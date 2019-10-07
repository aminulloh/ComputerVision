%----- Program untuk membersihkan nilai variable ---%
clc;
clear all;
%-----------------Program Utama -----------------------%
x = imread('rose.jpg');
sx = imref2d(size(x));
xg = rgb2gray(x);
xd = double(xg);
f = fft2(xd);
fa = log(abs(f));
fa = 255*fa/max(max(fa));
fs = fftshift(fa);
fb = uint8(fs);

figure()
subplot(1,2,1), imshow(xg,sx), title('Gambar input');
subplot(1,2,2), imshow(fb,sx), title('Frekuensi');
%-----------------End Program  -----------------------%