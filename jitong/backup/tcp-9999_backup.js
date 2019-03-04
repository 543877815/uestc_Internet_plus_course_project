var net = require('net');

var HOST = '127.0.0.1';
var PORT = 9999;

var client = new net.Socket();

var WebSocketServer = require('ws').Server,
wss = new WebSocketServer({port:8081});

var charArray = new Array();
var charlength = null;
var charStatus = 0;//传到第几帧
var eachCharLengthPerFrame = 5;
var eachBytePerChar = 16;
var columns = 4;
var lines = 4;
var newCharArray = new Array();

var receiveData = "";
var receiveChar = null;

var sendFlag = 200;
var sendFlagSuccess = 180;

client.connect(PORT, HOST, function() {
	console.log('CONNECTED TO: ' + HOST + ':' + PORT);
    // 建立连接后立即向服务器发送数据，服务器将收到这些数据 
    // var buffer = Buffer.from([1, 1, 0, 1, 1, 0]);
});
wss.on("connection", function(ws){
	console.log("client connected");
	ws.on("message", function(message) {
		//发回调试口
		charStatus = 0;
		newCharArray = new Array();
		// console.log("message receive is:" + message);
		//每个字符转换成二进制
		var charBinary = strToBinary(message);
		ws.send(strToBinary(charBinary));
		console.log("message change to binary is :" + charBinary);
		//分别将二进制装载入数组
		charArray = charBinary.split(" ");
		//构造含检验位的数组newArray
		charlength = charArray.length;
		for(var i = 0; i < charlength; i++){
			var totalOneNumber = 0;
			var totalOneNumberIn = 0;
			//为没满16位的字符二进制前加0
			while(charArray[i].length < eachBytePerChar){
				charArray[i] = "0" + charArray[i];
			}
			//将字符二进制拆分为数组
			var charElement = charArray[i].split("");
			//定义一个二维数组
			var twoDimensionArray = new Array();
			//组成一个5*4的数组，但是只有4*4有值
			for(var k = 0 ; k < lines + 1; k++){
				twoDimensionArray[k] = new Array();
				for(var j = 0 ; j < columns; j++){
					if(k == lines){
						twoDimensionArray[k][j] = null;
					}else{						
						twoDimensionArray[k][j] = charElement[k*lines+j];
						// console.log(twoDimensionArray[k][j]);
					}
				}
			}
			//为行加上校验位
			for(var k = 0 ; k < lines; k++){
				var oneNumber = 0;
				for(var j = 0 ; j < columns; j++){
					if(twoDimensionArray[k][j] == 1){
						oneNumber++;
						// totalOneNumber++;
					}
				}
				(oneNumber%2==0)?twoDimensionArray[k][columns]=0:twoDimensionArray[k][columns]=1;
				// console.log("line plus is" + twoDimensionArray[k][columns]);
				// console.log("oneNumber is:"  + oneNumber);
			}
			//为列加上校验位
			for(var j = 0 ; j < columns; j++){
				var oneNumber = 0;
				for (var k = 0 ; k < lines; k++){
					if(twoDimensionArray[k][j] == 1){
						totalOneNumberIn++;
						oneNumber++;
					}
				}
				(oneNumber%2==0)?twoDimensionArray[lines][j]=0:twoDimensionArray[lines][j]=1;
				// console.log("oneNumber is:"  + oneNumber);
				// console.log("column plus is:" + twoDimensionArray[lines][j]);
			}

			//总校验位
			for(var k = 0 ; k < lines+1; k++){
				for(var j = 0 ; j < columns+1; j++){
					if(twoDimensionArray[k][j] == 1){
						totalOneNumber++;
					}
				}
			}
			//为5-5加上校验位
			(totalOneNumber%2==0)?twoDimensionArray[lines][columns]=0:twoDimensionArray[lines][columns]=1;
			//将加上校验位的二维数组5*5转化为字符串
			newCharArray[i] = " ";
			for(var k = 0 ; k < lines + 1; k++){
				for(var j = 0 ; j < columns + 1; j++){
					newCharArray[i] += twoDimensionArray[k][j];
					// console.log(k + "line" + j + "column is " + twoDimensionArray[k][j])
				}
			}
			// console.log("newCharArray[i] is: " + newCharArray[i]);
			(totalOneNumberIn%2==0)?inside=0:inside=1;
			newCharArray[i] = newCharArray[i] + twoDimensionArray[lines][columns] + twoDimensionArray[lines][columns] + inside + inside + inside;//冗余技术
			console.log("newCharArray[i] is:" + newCharArray[i] );
			console.log(newCharArray[i]);
		}
		sendData(charStatus);
		
  //           // 完全关闭连接
  //           // client.destroy();
  //       });

});
	// 为客户端添加“data”事件处理函数
	// data是服务器发回的数据
	client.on('data', function(data) {
		// console.log('DATA: ' + new Uint8Array(data));
		var dataReceive = new Uint8Array(data);
		var postData = dataReceive.toString().replace(/,/g,"");
		console.log("normal array is:"+ postData);
		var reRendFlag = 0;
		var sendNextFlag = 0;
		for (var n= 0 ; n < dataReceive.length ; n++){
			dataReceive[n]==0?sendNextFlag++:reRendFlag++;
		}
		if(reRendFlag>sendFlagSuccess){
			console.log("resend");
			sendData(charStatus);
			return;
		}else if(sendNextFlag>sendFlagSuccess){
			charStatus += eachCharLengthPerFrame;
			if(charStatus > charlength){
				console.log("send end");
				sendNextOrFinishSend();
			}else{
				console.log("send next");
				sendData(charStatus);
			}
			return;
		}
		


	});
	// 为客户端添加“close”事件处理函数
	client.on('close', function() {
		console.log('Connection closed');
	});
});



//将字符串转换成二进制形式，中间用空格隔开
function strToBinary(str){
	var result = [];
	var list = str.split("");
	for(var i=0;i<list.length;i++){
		if(i != 0){
			result.push(" ");
		}
		var item = list[i];
		var binaryStr = item.charCodeAt().toString(2);
		result.push(binaryStr);
	}   
	return result.join("");
}

//将二进制字符串转换成Unicode字符串
function binaryToStr(str){
	var result = [];
	var list = str.split(" ");
	for(var i=0;i<list.length;i++){
		var item = list[i];
		var asciiCode = parseInt(item,2);
		var charValue = String.fromCharCode(asciiCode);
		result.push(charValue);
	}
	return result.join("");
}

function sendData(charStatus){
	var BeginAndEndFlag = "01111110";
	var sendData = "";
		//发送5帧
		for (var i = 0; i < eachCharLengthPerFrame ; i++){
			if(newCharArray[i+charStatus]){
				sendData += newCharArray[i+charStatus];
			}
		}
		//添加起始和终止标志位，并且将11111替换成111110
		sendData = sendData.replace(/ /g,'').replace(/11111/g,"111110");
		sendData = BeginAndEndFlag + sendData + BeginAndEndFlag;
		// console.log("sendData is:" + sendData);
		//将要发送的数据变成比特数组
		var sendDataArray = sendData.split("");
		// console.log("length is:" + sendDataArray.length);
		var dataBuffer = Buffer.from(sendDataArray);
		// console.log("buffer is:" + dataBuffer);
		client.write(dataBuffer);
	}

//重传函数
function reSend(){
    //定义一个全1的数组
    var a = [];for(var n = 0; n < sendFlag; n++) a[n] = 1;
    client.write(Buffer.from(a));
}
//传下一个、若发送方则告诉传完
function sendNextOrFinishSend(){
    //定义一个全0的数组
    var a = [];for(var n = 0; n < sendFlag; n++) a[n] = 0;
    client.write(Buffer.from(a));
}