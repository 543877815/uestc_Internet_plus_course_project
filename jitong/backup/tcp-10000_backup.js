var net = require('net');

var HOST = '127.0.0.1';
var PORT = 10000;

var WebSocketServer = require('ws').Server,
wss = new WebSocketServer({port:8082});

var client = new net.Socket();

var charArray = new Array();
var charlength = null;
var charStatus = 0;//传到第几帧
var eachCharLengthPerFrame = 5;
var eachBytePerChar = 16;
var columns = 4;
var lines = 4;
var newCharArray = new Array();
var excessNumber = 5;
var eachExcessNumber = 3;

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
        var totalOneNumber = 0;
        for(var i = 0; i < charlength; i++){
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
        }
        sendData(charStatus);
        
    });

    // 为客户端添加“data”事件处理函数
    // data是服务器发回的数据
    client.on('data', function(data) {
        //发送方
        //将二进制流转化成数组
        var dataReceive = new Uint8Array(data);
        var finishFlag = 0;
        var tempReceiveData = "";
        for (var n= 0 ; n < dataReceive.length ; n++){
            if(dataReceive[n]==0){finishFlag++;}
        }                                   
        if(finishFlag>sendFlagSuccess){
           console.log("finish");
           var json = {
            "data":receiveData,
            "type":"binary"
        }
        ws.send(JSON.stringify(json));
        // console.log("receiveData is:" + receiveData);

        receiveChar = binaryToStr(receiveData);
        // console.log("receiveChar is:" + receiveChar);
        receiveChar = null;
        receiveData = "";
        return;
    };
        //将数组变成字符串并去除','
        var dataString = dataReceive.toString().replace(/,/g,"");
        // console.log("normal string is:"+ dataString);
        //定义起始终止标志位
        var BeginAndEndFlag = "01111110";
        var flagLength = BeginAndEndFlag.length;
        //如果标志位改变，则发送111111....
        if(dataString.indexOf(BeginAndEndFlag)==dataString.lastIndexOf(BeginAndEndFlag)){
            //定义一个全1的数组
            reSend();
            return;
        }else{//如果不是，则发送00000.....
            //取出标志位之间的字符串
            dataString = dataString.substring(dataString.indexOf(BeginAndEndFlag)+flagLength, dataString.lastIndexOf(BeginAndEndFlag));
            // console.log("new data is:" + dataString);
            //将111110变成11111
            dataString = dataString.replace(/111110/g,"11111");
            // console.log('new data is:' + dataString);
            // console.log(dataString.length);
            // 判断有多少个字符
            var charNumber = dataString.length/((lines+1)*(columns+1)+excessNumber);
            // 如果不是整数则111110发生变化，重传
            if(charNumber!==parseInt(charNumber)){
                reSend();
                return;
            }
            var dataStringArray = new Array();
            // console.log("charNumber is:" + charNumber);
            for (var i = 0 ; i < charNumber ; i++){
                //每25+excessNumber个进行拆分
                dataStringArray[i] = dataString.substring((i*((lines+1)*(columns+1)+excessNumber)),((i+1)*((lines+1)*(columns+1)+excessNumber)));
                console.log(dataStringArray[i]);
                // 字符串转化为一维数组
                console.log(" dataStringArray[i] is:" +  dataStringArray[i]);
                var oneDemensionArray = dataStringArray[i].split("");
                //两个总控制位
                var excessOne = 0;
                for (var j = 0 ; j < excessNumber-eachExcessNumber+1; j++){
                    if(oneDemensionArray[lines*columns+j]==1) excessOne++;
                }
                (excessOne>=excessNumber-eachExcessNumber)?oneDemensionArray[(lines+1)*(columns+1)]=1:oneDemensionArray[(lines+1)*(columns+1)]=0;
                //字符串转化为5*5二维数组
                var twoDimensionArray = new Array();
                for (var j = 0 ; j < lines+1 ; j++){
                    var line = "";//D
                    twoDimensionArray[j] = new Array();
                    for (var k = 0 ; k < columns+1 ; k++){
                        twoDimensionArray[j][k] = oneDemensionArray[j*(lines+1)+k];
                        line = line + twoDimensionArray[j][k];//D
                    }
                    console.log(line);//D
                }

                var lineWrongVerify = null;
                var lineWrongVerifyNumber = 0;
                // 进行横向遍历检查校验位
                for (var j = 0 ; j < lines; j++){
                    // console.log("进行横向遍历")
                    var oneNumber = 0;
                    for (var k = 0 ; k < columns; k++){
                        if(twoDimensionArray[j][k]==1) oneNumber++;
                    }
                    //判断当今校验位是否与数据相等
                    var trueVerify = null;
                    oneNumber%2==0?trueVerify=0:trueVerify=1;
                    //如果不是
                    if(trueVerify!=twoDimensionArray[j][columns]){
                        //记录错误个数
                        lineWrongVerifyNumber++;
                        //记录当前错误位置
                        lineWrongVerify = j;
                        //若同行的校验位错误个数大于等于2，则要求重传
                        if(lineWrongVerifyNumber>=2){
                            reSend();
                            return;
                        }
                    }
                }
                var ColumnWrongVerify = null;
                var ColumnWrongVerifyNumber = 0;
                //进行纵向遍历
                for (var k = 0 ; k < columns; k++){
                    // console.log("进行纵向遍历")
                    var oneNumber = 0;
                    for (var j = 0 ; j < lines; j++){
                        if(twoDimensionArray[j][k]==1) oneNumber++;
                    }
                    var trueVerify = null;
                    oneNumber%2==0?trueVerify=0:trueVerify=1;
                    if(trueVerify!=twoDimensionArray[lines][k]){
                        ColumnWrongVerifyNumber++;
                        ColumnWrongVerify = k;
                        if(ColumnWrongVerifyNumber>=2){
                            reSend();
                            return;
                        }
                    }
                }
                // console.log(i);
                // console.log("ColumnWrongVerify is:" + ColumnWrongVerify);
                // console.log("lineWrongVerify is:" + lineWrongVerify);
                //差错检验与纠正
                if(ColumnWrongVerify!==null&&lineWrongVerify!==null){
                    // console.log("横纵检验各有一错")
                    var totalOneNumber = 0;
                    var trueVerify = null;
                    for (var j = 0 ; j < lines+1; j++){
                        for (var k = 0 ; k < columns+1; k++){
                            if(twoDimensionArray[j][k]==1) totalOneNumber++;
                        }
                    }
                    totalOneNumber%2==0?trueVerify=0:trueVerify=1;
                    //判断是两个标志位错还是一个数据位错误
                    if(twoDimensionArray[lines][columns] == trueVerify){//两个标志位错误
                        reSend();
                        return;
                    }else{//一个数据位错误
                        twoDimensionArray[lineWrongVerify][ColumnWrongVerify]==1?twoDimensionArray[lineWrongVerify][ColumnWrongVerify]=0:twoDimensionArray[lineWrongVerify][ColumnWrongVerify]=1;
                        // console.log("twoDimensionArray[lineWrongVerify][ColumnWrongVerify]:"+ twoDimensionArray[lineWrongVerify][ColumnWrongVerify]);
                    }
                }else if(ColumnWrongVerify!==null){
                    // console.log("纵检验有一错")
                    var excessInOne = 0;
                    var excessVerify = null;
                    for (var j = 0 ; j < excessNumber-eachExcessNumber+1; j++){
                        if(oneDemensionArray[(lines+1)*(columns+1)+eachExcessNumber+j]==1) excessInOne++;
                    }
                    (excessInOne>=(excessNumber-eachExcessNumber))?excessVerify=1:excessVerify=0;
                    var totalOneNumberIn = 0;
                    var trueVerify = null;
                    for (var j = 0 ; j < lines; j++){
                        for (var k = 0 ; k < columns; k++){
                            if(twoDimensionArray[j][k]==1) totalOneNumberIn++;
                        }
                    }
                    totalOneNumberIn%2==0?trueVerify=0:trueVerify=1;
                    if(trueVerify==excessVerify){
                        twoDimensionArray[lines][ColumnWrongVerify]==1?twoDimensionArray[lines][ColumnWrongVerify]=0:twoDimensionArray[lines][ColumnWrongVerify]=1;
                    }else{
                        reSend();
                        return;
                    }
                }else if(lineWrongVerify!==null){
                    // console.log("横检验有一错")
                    var excessInOne = 0;
                    var excessVerify = null;
                    for (var j = 0 ; j < excessNumber-eachExcessNumber+1; j++){
                        if(oneDemensionArray[(lines+1)*(columns+1)+eachExcessNumber+j]==1) excessInOne++;
                    }
                    (excessInOne>=excessNumber-eachExcessNumber)?excessVerify=1:excessVerify=0;
                    var totalOneNumberIn = 0;
                    var trueVerify = 0;
                    for (var j = 0 ; j < lines; j++){
                        for (var k = 0 ; k < columns; k++){
                            if(twoDimensionArray[j][k]==1) totalOneNumberIn++;
                        }
                    }
                    totalOneNumberIn%2==0?trueVerify=0:trueVerify=1;
                    if(trueVerify==excessVerify){
                        twoDimensionArray[lineWrongVerify][columns]==1?twoDimensionArray[lineWrongVerify][columns]=0:twoDimensionArray[lineWrongVerify][columns]=1;
                    }else{
                        reSend();
                        return;
                    }
                }
                // var newDataString= "";
                for(var j = 0 ; j < lines+1; j++){
                    var line = ""
                    for(var k = 0 ; k < columns+1; k++){
                        line += twoDimensionArray[j][k];
                    }
                    // console.log(line);
                }
                //二维数组转化为字符串
                var newDataString= "";
                for(var j = 0; j < lines; j++){
                    for(var k = 0 ; k < columns; k++){
                        newDataString += twoDimensionArray[j][k];
                    }
                }
                // console.log("newDataString is:" + newDataString + "  char:" + binaryToStr(newDataString)+ "\n");

                tempReceiveData = tempReceiveData + newDataString + " ";
            }
            var json = {
                "data" :  binaryToStr(tempReceiveData),
                "type" : "string"
            }
            ws.send(JSON.stringify(json));
            receiveData = receiveData + tempReceiveData;
            sendNext();
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
    console.log("reSend");
    var a = [];for(var n = 0; n < sendFlag; n++) a[n] = 1;
    client.write(Buffer.from(a));
}
//传下一个
function sendNext(){
    //定义一个全0的数组
    console.log("finish");
    var a = [];for(var n = 0; n < sendFlag; n++) a[n] = 0;
    client.write(Buffer.from(a));
}