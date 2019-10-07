%----- Program untuk membersihkan nilai variable ---%
clc;
clear all;
%-----------------Program Utama -----------------------%

a = imread('flower.jpg');
x = rgb2gray(a);

%----------------HPF Prewitt Masks---------------------%
px = [-1 0 1; -1 0 1; -1 0 1];
icx = filter2(px,x);
py = px';
icy = filter2(py,x);
pedge=sqrt(icx.^2+icy.^2);
%-----------------End Prewitt--------------------------%
%-----------------Low Pass Filter----------------------%
prewit = uint8(pedge);
%LPF dengan karnel 5x5
LFP = imfilter(prewit, ones(5)/25, 'symmetric');
%merubah gambar ke nilai negatif (inverse)
hasil = 255-LFP; 

figure(1) %Menampilkan gambar proses Prewitt Filter
subplot(1,3,1),imshow(icy/255),title('HPF Horizontal (X-axis)');
subplot(1,3,2),imshow(icx/255),title('HPF Vertical (Y-axis)');
subplot(1,3,3),imshow(pedge/255),title('HPF Prewitt');

figure(2) %Menampilkan gambar perbandingan original vs sketch
subplot(1,2,1),imshow(x),title('Original Image');
subplot(1,2,2),imshow(hasil),title('Sketch Effect');




%--------------------------HPF Laplacian-------------------------%

% lab=[0 1 0;1 -4 1;0 1 0];
% result=uint8(filter2(lab,x,'same'));
% final2 = 255-result;
% %median = medfilt2(final);
% 
% figure(2)
% subplot(1,3,1),imshow(x),title('Original Image');
% subplot(1,3,2),imshow(result),title('HPF Laplacian');
% subplot(1,3,3),imshow(final2),title('Sketch Effect');
% 
% add = imadd(final1,xx);
% add1 = imadd(add,final2);
% figure(3)
% subplot(131),imshow(pd);
% subplot(132),imshow(result);
% subplot(133),imshow(add);
% 
% hasil = 255-add;
% median = medfilt2(hasil);
% 
% figure(4)
% subplot(121),imshow(add);
% subplot(122),imshow(add1);


