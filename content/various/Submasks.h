/**
 * Author: coderats 
 * Date: 2025-11-06
 * License: Unknown
 * Source: coderats 
 * Description: Enumerate every mask and submasks
 * Time: $O(3 ^ n)$ 
 * Status: tested  
 */
#pragma once

for (int m=0; m<(1<<n); ++m)
    for (int s=m; s; s=(s-1)&m)
 ... s and m ... /// procesar submask