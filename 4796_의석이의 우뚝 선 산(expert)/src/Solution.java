import java.util.Scanner;

public class Solution {
	private static int testCase;
	private static int[] h;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		testCase = sc.nextInt();
		for(int count = 1; count <= testCase; count++) {
			int N = sc.nextInt();
			int result = 0;
			h = new int[N];
			for(int i = 0; i < N; i++) {
				h[i] = sc.nextInt();
			}
			int left = 0;
			int right = 0;
			int i;
			for(i = 0; i < N-1; i++) {
				while((i + 1 < N) && h[i] < h[i+1]) {
					left++;
					i++;
				}
				while((i + 1 < N) && h[i] > h[i+1]) {
					right++;
					i++;
				}
				if((i + 1 < N) && h[i] < h[i+1]) {
					result += left * right;
					left = right = 0;
				}
				i--;
			}
			result += left * right;
			System.out.println("#" + count + " " + result);
			result = 0;
		}

	}

}
