%----- Program untuk membersihkan nilai variable ---%
clc;
clear all;
%--------------Program Utama -----------------------%
%program untuk membaca gambar dan menyimpan pada variable y
y = imread('air (10).jpg'); %air (10).jpg adalah nama gambar yang di panggil.

RC = y(:,:,1);
GC = y(:,:,2);
BC = y(:,:,3);

%Program untuk mencari nilai minimal dan maksimal dari pixel gambar y.
RCmin=min(min(RC));
RCmax=max(max(RC));

GCmin=min(min(GC));
GCmax=max(max(GC));

BCmin=min(min(BC));
BCmax=max(max(BC));

%Program untuk mencari nilai mean minimal dan maksimal pada pixel gambar y.
% ymmin=mean(mean(ymin));
% ymmax=mean(mean(ymax));

%Program Auto-level pada gambar ang disimpan pada variabel y ke y1
y1=255/(ymmax-ymmin)*(y-ymmin);
%Program untuk mencari nilai minimal dan maksimal dari pixel gambar y1.
y1min=min(min(y1));
y1max=max(max(y1));
%Program untuk mencari nilai mean minimal dan maksimal pada pixel gambar y1.
y1mmin=mean(mean(y1min));
y1mmax=mean(mean(y1max));


%Histogram Equalization
subplot(2,2,1),imshow(y);
title('original image');

histeq = histeq(rgb2gray(y));
subplot(2,2,2), imshow(histeq);
title('histeq image');

subplot(2,2,3), imhist(rgb2gray(y));
title('histogram original image');

subplot(2,2,4), imhist(histeq);
title('histogram original image');

% 
% %Program untuk menampilkan gambar original.
% subplot(2,2,1);
% imshow(y);
% h = gca;
% h.Visible = 'On';
% title('Original Image');
% %Program untuk menampilkan gambar hasil Auto-level
% subplot(2,2,2), 
% imshow(y1),
% h = gca;
% h.Visible = 'On';
% title('Auto-level Image');
% %Program untuk menampilkan histogram dari gambar original.
% subplot(2,2,3), imhist(rgb2gray(y)), title('Original Histogram');
% text(120,12000,sprintf('Min=%.2f and Max=%.2f',ymmin, ymmax));
% %Program untuk menampilkan histogram dari gambar hasil Auto-level.
% subplot(2,2,4), imhist(rgb2gray(y1)), title('Autolevel Histogram');
% text(120,12000,sprintf('Min=%.2f and Max=%.2f',y1mmin, y1mmax));
