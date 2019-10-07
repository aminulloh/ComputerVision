%----- Program untuk membersihkan nilai variable ---%
clc;
clear all;
%-----------------Program Utama -----------------------%
x1 = imread('wood1.jpg');
x2 = imread('wood2.jpeg');
x3 = imread('wood3.jpg');
x4 = imread('wood4.jpeg');
x5 = imread('wood5.jpg');

sx1 = imref2d(size(x1));
sx2 = imref2d(size(x2));
sx3 = imref2d(size(x3));
sx4 = imref2d(size(x4));
sx5 = imref2d(size(x5));

xg1=rgb2gray(x1);
xg2=rgb2gray(x2);
xg3=rgb2gray(x3);
xg4=rgb2gray(x4);
xg5=rgb2gray(x5);

xd1 = double(xg1);
xd2 = double(xg2);
xd3 = double(xg3);
xd4 = double(xg4);
xd5 = double(xg5);

f1 = fft2(xd1);
f2 = fft2(xd2);
f3 = fft2(xd3);
f4 = fft2(xd4);
f5 = fft2(xd5);


fa1 = log(abs(f1));
fa2 = log(abs(f2));
fa3 = log(abs(f3));
fa4 = log(abs(f4));
fa5 = log(abs(f5));

fa1 = 255*fa1/max(max(fa1));
fa2 = 255*fa2/max(max(fa2));
fa3 = 255*fa3/max(max(fa3));
fa4 = 255*fa4/max(max(fa4));
fa5 = 255*fa5/max(max(fa5));

fs1 = fftshift(fa1);
fs2 = fftshift(fa2);
fs3 = fftshift(fa3);
fs4 = fftshift(fa4);
fs5 = fftshift(fa5);

fb1 = uint8(fs1);
fb2 = uint8(fs2);
fb3 = uint8(fs3);
fb4 = uint8(fs4);
fb5 = uint8(fs5);

figure(1)
subplot(2,5,1), imshow(xg1,sx1),title('Gambar 1');
subplot(2,5,2), imshow(xg2,sx2),title('Gambar 2');
subplot(2,5,3), imshow(xg3,sx3),title('Gambar 3');
subplot(2,5,4), imshow(xg4,sx4),title('Gambar 4');
subplot(2,5,5), imshow(xg5,sx5),title('Gambar 5');
subplot(2,5,6), imshow(fb1,sx1),title('Frekuensi 1');
subplot(2,5,7), imshow(fb2,sx2),title('Frekuensi 2');
subplot(2,5,8), imshow(fb3,sx3),title('Frekuensi 3');
subplot(2,5,9), imshow(fb4,sx4),title('Frekuensi 4');
subplot(2,5,10), imshow(fb5,sx5),title('Frekuensi 5');