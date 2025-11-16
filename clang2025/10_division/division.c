#include <stdio.h>
#define POLY_LEN 20 // 입력 조건에 있었던 입력 다항식 차수의 최대

void scan_poly(int *poly, int *deg) {
    scanf("%d" ,deg);
    *deg -= 1;
    for (int i = *deg ; i >= 0 ; i--) {
        scanf("%d", poly + i);
    }
}

void print_poly(int *poly, int deg) {
    if (deg == -1) { printf("1\n0\n"); return; }
    printf("%d\n", deg + 1);
    for(int i = deg ; i >= 0 ; i--) printf("%d ", poly[i]);
    printf("\n");
}

int main() {
    int poly1[POLY_LEN + 1] = {}, poly1_deg; // 나눠지는 대상
    int poly2[POLY_LEN + 1] = {}, poly2_deg; // 나눌 다항식

    scan_poly(poly1, &poly1_deg);
    scan_poly(poly2, &poly2_deg);

    // 굳이 필요가 없으나 poly1의 불변성을 위해 깊은 복사
    int remainder[POLY_LEN + 1] = {};
    for (int i = 0 ; i <= poly1_deg ; i++) remainder[i] = poly1[i];
    
    int result[POLY_LEN + 1] = {};
    int result_deg = poly1_deg - poly2_deg;
    for (int i = result_deg ; i >= 0 ; i--) {
        result[i] = remainder[i + poly2_deg] / poly2[poly2_deg]; // 해당 차의 몫 계산
        
        // 구한 몫만큼을 빼 나가면 remainder에 나머지가 남음
        for (int j = 0 ; j <= poly2_deg ; j++) {
            remainder[i + j] -= result[i] * poly2[j];
        }
    }
    
    // 나머지의 차수는 확실치 않으므로 직접 셈
    int remainder_deg = poly2_deg - 1;
    while (remainder_deg >= 0 && remainder[remainder_deg] == 0) remainder_deg--;

    print_poly(result, result_deg);
    print_poly(remainder, remainder_deg);
}