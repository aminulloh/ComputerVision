clc;
clear all;

I = imread('Picture1.jpg');
[Ir Ic] = size(I);
figure(1);
imshow(I);

T = imread('temp1.jpg');
[Tr Tc] = size(T);
figure(2)
imshow(T);

R = normxcorr2(T,I)
R = imcrop(R,[Tc Tr Ic Ir]);
[r c v] = find(R==(max(max(R))))
RGB = insertShape(I, 'rectangle',[c r Tc Tr], 'LineWidth', 3);
figure(3)
imshow(RGB)