import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Stack;

public class Solution {
	static class Point{
		int x;
		int y;
		Point(int x, int y){
			this.x = x;
			this.y = y;
		}
		@Override
		public String toString() {
			return "Point [x=" + x + ", y=" + y + "]";
		}
		
	}
	
	private static int testCase, N, min = Integer.MAX_VALUE;
	private static Stack<Integer> stack;
	private static boolean[] visited;
	private static List<Point> points;
	private static Point start, end;

	private static void permutation(int depth) {
		if(depth == N) {
			int path = 0;
			path +=  Math.abs(start.x-points.get(stack.get(0)).x) + Math.abs(start.y-points.get(stack.get(0)).y);
			for(int i = 0; i < N-1; i++) {
				path += Math.abs(points.get(stack.get(i)).x-points.get(stack.get(i+1)).x) + Math.abs(points.get(stack.get(i)).y-points.get(stack.get(i+1)).y);
			}
			path +=  Math.abs(points.get(stack.get(N-1)).x-end.x) + Math.abs(points.get(stack.get(N-1)).y-end.y);
			min = Math.min(min, path);
			return;
		}
		for(int i = 0; i < N; i++) {
			if(visited[i]) continue;
			visited[i] = true;
			stack.push(i);
			permutation(depth + 1);
			stack.pop();
			visited[i] = false;
		}
	}
	
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		testCase = sc.nextInt();
		
		for(int test = 1; test <= testCase; test++) {
			N = sc.nextInt();
			points = new ArrayList<>();
			stack = new Stack<>();
			visited = new boolean[N];
			start = new Point(sc.nextInt(), sc.nextInt());
			end = new Point(sc.nextInt(), sc.nextInt());
			for(int i = 0; i < N; i++) {
				points.add(new Point(sc.nextInt(), sc.nextInt()));
			}
			permutation(0);
			System.out.println("#" + test + " " + min);
			min = Integer.MAX_VALUE;
		}

	}

}
