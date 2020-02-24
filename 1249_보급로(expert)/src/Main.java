import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.PriorityQueue;

public class Main {
	static class Point implements Comparable<Point>{
		int i;
		int j;
		int cost;
		Point(int i, int j, int cost){
			this.i = i;
			this.j = j;
			this.cost = cost;
		}
		
		@Override
		public String toString() {
			return "Point [i=" + i + ", j=" + j + ", cost=" + cost + "]";
		}

		@Override
		public int compareTo(Point o) {
			return Integer.compare(this.cost, o.cost);
		}
		
	}
	private static int testCase, N, result;
	private static String[] line;
	private static int[][] map;
	private static int[][] dir = {{1,0},{0,1},{-1,0},{0,-1}};
	private static boolean[][] visited;
	
	private static void bfs(Point start) {
		PriorityQueue<Point> q = new PriorityQueue<>();
		q.offer(start);
		
		while(!q.isEmpty()) {
			Point cur = q.poll();
			visited[cur.i][cur.j] = true;
			if(cur.i == N-1 && cur.j == N-1) {
				result = cur.cost;
				break;
			}
			for(int k = 0; k < 4; k++) {
				int nextI = cur.i + dir[k][0];
				int nextJ = cur.j + dir[k][1];
				if(nextI < 0 || nextI >= N || nextJ < 0 || nextJ >= N) continue;
				if(visited[nextI][nextJ]) continue;
				visited[nextI][nextJ] = true;
				q.offer(new Point(nextI, nextJ, cur.cost + map[nextI][nextJ]));
			}
		}
	}
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		testCase = Integer.parseInt(br.readLine());
		for(int count = 1; count <= testCase; count++) {
			N = Integer.parseInt(br.readLine());
			map = new int[N][N];
			visited = new boolean[N][N];
			for(int i = 0; i < N; i++) {
				line = br.readLine().split(""); 
				for(int j = 0; j < N; j++) {
					map[i][j] = Integer.parseInt(line[j]);
				}
			}
			bfs(new Point(0, 0, 0));
			System.out.println("#" + count + " " + result);
		}
	}
}
