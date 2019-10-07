
%----- Program untuk membersihkan nilai variable ---%
clc;
clear all;
%-----------------Program Utama -----------------------%
a = imread('apple.jpeg'); %nama gambar yg di proses

y1 = imresize(a, 1);
y2 = imresize(a, 1/2);
y3 = imresize(a, 1/4);
y4 = imresize(a, 1/8);
y5 = imresize(a, 1/16);
y6 = imresize(a, 1/32);
y7 = imresize(a, 1/64);
y8 = imresize(a, 1/128);
y9 = imresize(a, 1/256);
y10 = imresize(a, 1/512);

figure(1)
subplot(2,5,1), imshow(y1),title('Skala = 1');
subplot(2,5,2), imshow(y2),title('Skala = 1/2');
subplot(2,5,3), imshow(y3),title('Skala = 1/4');
subplot(2,5,4), imshow(y4),title('Skala = 1/8');
subplot(2,5,5), imshow(y5),title('Skala = 1/16');
subplot(2,5,6), imshow(y6),title('Skala = 1/32');
subplot(2,5,7), imshow(y7),title('Skala = 1/64');
subplot(2,5,8), imshow(y8),title('Skala = 1/128');
subplot(2,5,9), imshow(y9),title('Skala = 1/256');
subplot(2,5,10), imshow(y10),title('Skala = 1/512');

%-----------------End Program-----------------------%
