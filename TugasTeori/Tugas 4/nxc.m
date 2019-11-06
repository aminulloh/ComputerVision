% Membaca Gambar
x=imread('2.jpg');
xg=rgb2gray(x);
% Membaca Tempelate
p=imread('2b.jpg');
pg=rgb2gray(p);

xd=double(xg);
pd=double(pg);

% Filter Gambar
yd=normxcorr2(pd,xd);
yd=255*yd/max(max(yd));
y=uint8(yd);
zd=255*(yd>140);
z=uint8(zd);

% Menampilkan Gambar Hasil
figure(1)
subplot(1,3,1), imshow(x), title('Image Asli')
subplot(1,3,2), imshow(y), title('Hasil Filter')
subplot(1,3,3), imshow(z), title('Thresholding')