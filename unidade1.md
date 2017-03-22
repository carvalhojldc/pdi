# [Página principal](index.md)
## [Unidade 1] - [Unidade 2](#) - [Unidade 3](#)

### Exercício 1
Negativar a região de uma imagem

![useful image](image/ex3.2.1t.png) ![useful image](image/ex3.2.1.png)

```c++
#include <iostream>
#include <opencv2/opencv.hpp>

struct Ponto {
	int x;
	int y;
};

int main(int argc, char** argv) {
	
	[..] 
	
	for(int x=ponto1.x; x<=ponto2.x; x++) {
		for(int y=ponto1.y; y<=ponto2.y; y++) {
			image.at<uchar>(x,y)= 255 - image.at<uchar>(x,y);
		}
	}
	
	[...]
	
	return 0;
}
```
[Source code](code/ex3.2.1.cpp)

### Exercício 2
Trocar os quadrantes em diagonal de uma imagem
[Source code](code/ex3.2.2.cpp)
