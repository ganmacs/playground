import java.util.*;

public class A {
    public static int INF = 10000000;

    public static void main(String[] args) {
        Scanner sr = new Scanner(System.in);
        int in = sr.nextInt();
        double d = in / 1000;

        if (in < 0.1) {
            System.out.println("00");
        } else if(in >= 0.1 && in <= 5) {
            System.out.printf("%02d", in * 10);
        } else if(in >= 6 && in < 30) {
            System.out.printf("%02d", in * 10);
        } else if(in >= 35 && in < 70) {
            System.out.println(in + 50);
        } else if (in > 70) {
            System.out.printf(89);
        }
    }
}


// 0.1km 未満： VVの値は 00 とする。
// 0.1km 以上 5km 以下：距離 (km) を 10 倍した値とする。1 桁の場合は上位に 0 を付す。
// 6km 以上 30km 以下：距離 (km) に 50 を足した値とする。
// 35km 以上 70km 以下：距離 (km) から 30 を引いて 5 で割った後、80 を足した値とする。
// 70km より大きい：VVの値は 89 とする。
