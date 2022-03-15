#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

const double eps = 1e-12;
struct Point {
    double x, y;
};

double getArea(vector<Point>& arr) {
    int n = arr.size();
    double ans = 0;
    for (int i = 0; i < n; i++) {
        Point& a = arr[i];
        Point& b = arr[(i + 1) % n];
        ans += a.x * b.y - a.y * b.x;
    }
    return abs(ans / 2);
}

double getDist(Point& a, Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

Point getPoint(Point& a, Point& b, double dist) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double maxDist = getDist(a, b);
    double per = dist / maxDist;
    dx *= per;
    dy *= per;
    return (Point) {a.x + dx, a.y + dy};
}

double getConvexArea(vector<Point>& arr, int k) {
    int n = arr.size();
    double tar = 0;
    for (int i = 0; i + 1 < n; i++) {
        tar += getDist(arr[i], arr[i + 1]);
    }
    tar /= k;

    vector<Point> ans = {arr[0]};
    Point curPoint = arr[0];
    int nextId = 1;
    for (int i = 1; i < k; i++) {
        double now = 0;
        while (1) {
            double maxDist = getDist(curPoint, arr[nextId]);
            if (now + maxDist - tar < -eps) {
                now += maxDist;
                curPoint = arr[nextId];
                nextId++;
            } else {
                Point nextPoint = getPoint(curPoint, arr[nextId], tar - now);
                ans.push_back(nextPoint);
                curPoint = nextPoint;
                break;
            }
        }
    }

    return getArea(ans);
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<Point> arr;
    for (int i = 0; i < n; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        arr.push_back({x, y});
    }

    double ans = 1e100;
    vector<Point> out;
    for (int i = 0; i < n; i++) {
        Point a = arr[i];
        Point b = arr[(i + 1) % n];
        double maxDist = getDist(a, b);
        double l = 0, r = maxDist;
        for (int j = 0; j < 35; j++) {
            double m1 = (l * 17 + r * 15) / 32;
            double m2 = (l * 15 + r * 17) / 32;
            double area1 = 0;
            double area2 = 0;

            vector<Point> tmp;
            Point startPoint = getPoint(a, b, m1);
            tmp.push_back(startPoint);
            for (int k = 0; k < n; k++) {
                tmp.push_back(arr[(i + 1 + k) % n]);
            }
            tmp.push_back(startPoint);
            area1 = getConvexArea(tmp, k);

            startPoint = getPoint(a, b, m2);
            tmp[0] = startPoint;
            tmp.back() = startPoint;
            area2 = getConvexArea(tmp, k);
            if (area1 < area2) r = m2;
            else l = m1;

            ans = min(ans, area1);
            ans = min(ans, area2);
        }

        vector<Point> tmp = {arr[i]};
        for (int j = 1; j <= n; j++) {
            tmp.push_back(arr[(i + j) % n]);
        }
        tmp.push_back(arr[i]);
        double area = getConvexArea(tmp, k);
        ans = min(ans, area);

    }
    printf("%.10lf\n", ans);
}
