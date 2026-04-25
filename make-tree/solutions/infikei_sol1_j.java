import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class n_maketree_test {

    static class Pair {
        int a, b;

        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }

    static int[] parents = new int[100001];

    static void initParents(int n) {
        for (int u = 0; u <= n; u++) {
            parents[u] = -1;
        }
    }

    static int getParentOf(int u) {
        if (parents[u] < 0) return u;
        return parents[u] = getParentOf(parents[u]);
    }

    static boolean unionParents(int u1, int u2) {
        int pu1 = getParentOf(u1);
        int pu2 = getParentOf(u2);

        if (pu1 == pu2) return false;

        if (parents[pu1] < parents[pu2]) {
            parents[pu1] += parents[pu2];
            parents[pu2] = pu1;
        }
        else {
            parents[pu2] += parents[pu1];
            parents[pu1] = pu2;
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine(), " ");
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());

        initParents(n);

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine(), " ");
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());

            if (!unionParents(u, v)) {
                System.out.println(0);
                return;
            }
        }

        ArrayList<Integer> components = new ArrayList<Integer>();

        for (int u = 1; u <= n; u++) {
            if (parents[u] < 0) {
                components.add(-parents[u]);
            }
        }

        int cs = components.size();

        if (cs >= 7) {
            System.out.println(-1);
            return;
        }

        int ces = cs * (cs - 1) / 2;
        Pair[] componentEdges = new Pair[ces];

        for (int i = 0, idx = 0; i < cs; i++) {
            for (int j = i + 1; j < cs; j++) {
                componentEdges[idx++] = new Pair(i, j);
            }
        }

        long ans = 0;

        for (int bits = 0; bits < (1 << ces); bits++) {
            int bit_cnt = 0;

            for (int i = 0; i < ces; i++) {
                if ((bits & (1 << i)) != 0) {
                    bit_cnt++;
                }
            }

            if (bit_cnt != cs - 1) continue;

            initParents(cs);
            long cnt = 1;

            for (int i = 0; i < ces; i++) {
                if ((bits & (1 << i)) != 0) {
                    Pair componentEdge = componentEdges[i];
                    int c1 = componentEdge.a;
                    int c2 = componentEdge.b;

                    if (!unionParents(c1, c2)) {
                        cnt = -1;
                        break;
                    }

                    cnt *= components.get(c1);

                    if (cnt > k) {
                        System.out.println(-1);
                        return;
                    }

                    cnt *= components.get(c2);

                    if (cnt > k) {
                        System.out.println(-1);
                        return;
                    }
                }
            }

            if (cnt == -1) continue;

            ans += cnt;

            if (ans > k) {
                System.out.println(-1);
                return;
            }
        }

        System.out.println(ans);

        br.close();
    }

}
