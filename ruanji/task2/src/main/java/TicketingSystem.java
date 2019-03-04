public class TicketingSystem {
    public static void main(String args[]) {
        Service service = new Service("北京-->赣州", 500);
        TicketSaler ticketSaler = new TicketSaler("售票程序", service);
        //创建8个线程，以模拟8个窗口
        Thread threads[] = new Thread[8];
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new Thread(ticketSaler, "窗口" + (i + 1));
            System.out.println("窗口" + (i + 1) + "开始出售 " + service.getTicketName() + " 的票...");
            threads[i].start();
        }

    }
    /**
     * 模拟服务器的类
     */
    static class Service {
        private String ticketName;    //票名
        private int totalCount;        //总票数
        private int remaining;        //剩余票数

        public Service(String ticketName, int totalCount) {
            this.ticketName = ticketName;
            this.totalCount = totalCount;
            this.remaining = totalCount;
        }

        public synchronized int saleTicket(int ticketNum) {
            if (remaining > 0) {
                remaining -= ticketNum;
                try {        //暂停0.1秒，模拟真实系统中复杂计算所用的时间
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                if (remaining >= 0) {
                    return remaining;
                } else {
                    remaining += ticketNum;
                    return -1;
                }
            }
            return -1;
        }

        public synchronized int getRemaining() {
            return remaining;
        }

        public String getTicketName() {
            return this.ticketName;
        }

    }

    /**
     * 售票程序
     */
    static class TicketSaler implements Runnable {
        private String name;
        private Service service;

        public TicketSaler(String windowName, Service service) {
            this.name = windowName;
            this.service = service;
        }

        @Override
        public void run() {
            while (service.getRemaining() > 0) {
                synchronized (this)
                {
                    System.out.print(Thread.currentThread().getName() + "出售第" + service.getRemaining() + "张票，");
                    int remaining = service.saleTicket(1);
                    if (remaining >= 0) {
                        System.out.println("出票成功!剩余" + remaining + "张票.");
                    } else {
                        System.out.println("出票失败！该票已售完。");
                    }
                }
            }
        }
    }
}
