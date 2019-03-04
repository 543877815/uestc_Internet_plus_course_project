
import java.io.*;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;
import java.util.Date;

public class lockTest {
    public static void main(String[] args) throws InterruptedException {

        //文件锁所在文件
        File lockFile = new File("src/main/resources/test.xls");
        FileOutputStream outStream = null;
        FileInputStream inputStream = null;
        FileLock lock = null;

        try {
            outStream = new FileOutputStream(lockFile);
//            inputStream = new FileInputStream(lockFile);
            FileChannel channel = outStream.getChannel();
            try {
                //方法一
//                lock = channel.lock();
//                System.out.println("Get the Lock!");
//                Thread.sleep(10000);
                //do something...

                //方法二
                lock = channel.tryLock();
                if (lock != null) {
                    System.out.println("Get the Lock!");
                    Thread.sleep(10000);
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            if (null != lock) {
                try {
                    System.out.println("Release The Lock" + new Date().toString());
                    lock.release();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if (outStream != null) {
                try {
                    outStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}