import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * @ClassName: ReadWriteLockTest
 * @author whwang
 * @date 2012-1-11 下午02:20:59
 */
public class ReadWriteLockTest {

    static ReentrantReadWriteLock lock = new ReentrantReadWriteLock(true);

    public static void main(String[] args) {
        // 是否可以进入多个reader - 可以

        // 是否可以进入多个writer - 不可以

        // 当有reader进入后, writer是否可以进入 - 不可以

        // 当有writer进入后, reader是否可以进入 - 不可以

        MyThread t1 = new MyThread(0, "t1");
        MyThread t2 = new MyThread(0, "t2");
        MyThread t3 = new MyThread(1, "t3");
        t1.start();
        t2.start();
        t3.start();
    }

    private static class MyThread extends Thread {

        private int type;

        private String threadName;

        public MyThread(int type, String threadName) {
            this.threadName = threadName;
            this.type = type;
        }

        @Override
        public void run() {
            while (true) {
                if (type == 0) {
                    // read
                    ReentrantReadWriteLock.ReadLock readLock = null;
                    try {
                        readLock = lock.readLock();
                        readLock.lock();
                        System.err.println("to read...." + threadName);
                        try {
                            Thread.sleep(5 * 1000);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    } finally {
                        readLock.unlock();
                    }
                } else {
                    // write
                    ReentrantReadWriteLock.WriteLock writeLock = null;
                    try {
                        writeLock = lock.writeLock();
                        writeLock.lock();
                        System.err.println("to write...." + threadName);
                        try {
                            Thread.sleep(5 * 1000);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    } finally {
                        writeLock.unlock();
                    }
                }
            }
        }
    }
}