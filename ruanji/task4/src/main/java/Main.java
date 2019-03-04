import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("=================欢迎来到互联网+智慧物流质询系统===============");
        while (true) {
            System.out.println("----------请选择操作----------");
            System.out.println("1.物流管理系统");
            System.out.println("2.数据管理系统");
            System.out.println("3.数据库操作");
            System.out.println();
            System.out.println("0.退出系统");
            try {
                Scanner input = new Scanner(System.in);
                int inputValue = input.nextInt();
                if (inputValue == 0) {
                    System.out.println("--------------系统登出-------------");
                    return;
                } else if (inputValue == 1) {
                    new Main1().main(args);
                } else if (inputValue == 2) {
                    new Main2().main(args);
                } else if (inputValue == 3) {
                    new Main3().main(args);
                } else {
                    System.out.println("输入错误！请重新输入！");
                }
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("输入错误！请重新输入！");
            }
        }
    }
}
