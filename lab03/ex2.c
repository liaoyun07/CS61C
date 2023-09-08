int source[] = {3, 1, 4, 1, 5, 9, 0};
int dest[10];

int fun(int x) {
	return -x * (x + 1);
}

int main() {
    int k; //t0
    int sum = 0;//s0
    for (k = 0; source[k] != 0; k++) {
        dest[k] = fun(source[k]);//t2
        sum += dest[k];
    }
    return sum;
}