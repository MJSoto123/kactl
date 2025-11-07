/**
 * Author: coderats 
 * Date: 2025-11-06
 * License: Unknown
 * Source: coderats 
 * Description: Check definition.
 * Time: $O(N \log \log N)$ 
 * Status: tested  
 */
#pragma once
const int MX = 1e6;
short mu[MX+1] = {0, 1};
///  O(MX log(log(MX)))
void mobius() {
    for (int i = 1; i <= MX; i++) {
        if (!mu[i]) continue;
        for (int j = i*2; j <= MX; j += i) {
            mu[j] -= mu[i];
        }
    }
}
