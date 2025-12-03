# 코드

```c
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
```

# 해설

알고리즘 자체는 익숙한 구조입니다.

나눌 식의 최고차항부터 차수를 하나씩 깎아나갈 수 있도록 몫의 해당 차의 계수를 얻어 나가면 됩니다.

아마 그렇게 피제수의 차수를 깎아 나간 후 결국에 피제수가 제수의 차수보다 작아진다면 그것이 최종 나머지일 것이므로 그 결과를 출력하면 됩니다.

특별히 주의할 점이라면, 나머지의 차수가 항상 제수의 차수 - 1은 아닐 것이므로 실제로 나머지의 차수가 몇인지는 직접 세어 봐야 정해진 출력 방식을 제대로 따를 수 있습니다.

코드를 깔끔하게 쓰는 부분에서는 고려한 것이 두 가지가 있습니다.

1. 다항식을 어떻게 저장할 것인가.
2. 다항식 배열의 불변성

다항식은 N차일 경우 N+1개의 숫자로 표현할 수 있습니다.
이를 구조체로 표현할 수도 있겠지만 당장 구현해야 할 것은 나눗셈뿐이므로 간단하게 길이 21(문제 조건에 적힌 다항식의 최대 차수)으로 선언된 배열로, 오름차순으로 저장하기로 하고, 다항식의 차수는 별개의 변수에 저장하는 방식으로 설계했습니다.

주어진 입력은 내림차순으로 되어 있으나, 값에 접근할 때 "n차항은 배열의 n번 인덱스에 있음"이 직관적이고 처리하기 편하다는 점에서 입력과 출력 시점에 순서를 뒤집어 내부에서는 오름차순으로 저장하게 만들었습니다.

또한 현재 코드에서는 값을 한 번 나누고 끝이라서 별 필요성이 없으나.
지금 알고리즘으로는 나누는 대상 배열에서 연산 후 원래의 피제수가 사라지는 문제가 있습니다.

이렇게 연산 후 원래 값이 사라져 버린다면, 디버깅 중에 내가 입력을 제대로 받은 건지 확인할 때 귀찮은 상황이 생길 수도 있고, 더 중요하게는 만약 여기에서 이 피제수를 다시 사용할 일이 생겼는데 실수로 이미 값이 바뀌어 있다는 걸 고려하지 않고 코드를 짠다면 치명적인 버그가 발생할 수도 있습니다.

따라서 이러한 경우에는 다른 변수를 선언하고 그 내부 값을 완전히 옮겨준 다음 그 변수에서 필요한 연산을 진행하는 것이 바람직합니다.

또한 이렇게 하면 poly1은 첫 번째 입력받은 다항식(피제수), remainder는 나눗셈을 한 후 남은 나머지로써 의미 구분도 명확히 되기 때문에 코드의 가독성도 향상된다고 볼 수 있습니다.

이 문제는 본인이 직접 계산하라고 하면 모두가 할 수 있기 때문에 계산 알고리즘 자체를 떠올리지 못하는 사람은 없었을 거라 봅니다.따라서 자신이 머릿속에 생각하고 있는 계산 절차를 실제 코드로 구체화시키면서 직관적으로 이해 가능한 방식으로 풀어내는 능력이 중요했다고 봅니다.