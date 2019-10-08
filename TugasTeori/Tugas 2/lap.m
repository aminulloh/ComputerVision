
%----- Program untuk membersihkan nilai variable ---%
clc;
clear all;
%-----------------Program Utama -----------------------%

a = imread('defira.jpg');
I = rgb2gray(a);
x = imgaussfilt(I,1);


%--------------------------HPF Laplacian-------------------------%

lab=[0 1 0;1 -4 1;0 1 0];
result=uint8(filter2(lab,x,'same'));
final = 255-result;
median = medfilt2(final);

figure(1)
subplot(1,3,1),imshow(x),title('Original Image');
subplot(1,3,2),imshow(result),title('HPF Laplacian');
subplot(1,3,3),imshow(final),title('Sketch Effect');

figure(2)
imshow(final);