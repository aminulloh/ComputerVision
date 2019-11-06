clc;
clear;

%Membaca gambar
x=imread('2.jpg');
xg=rgb2gray(x);
xd=double(xg);
xdm=mean(mean(xd));
xd=xd-xdm;

%Membaca template
h1=imread('2b.jpg');
h2=rgb2gray(h1);
hd=double(h2);
h3=hd/sum(sum(hd));
hm=mean(mean(h3));
h=h3-hm;

%Proses filtering
yd=filter2(h,xd);
ymax=max(max(yd));
y1=yd*255/ymax;
y=uint8(y1);

%Proses thresholding
th=0.65;
y2=(yd>=th*ymax);
y3=yd.*y2;
y4=y3*255/ymax;
y5=uint8(y4);

%Mwnampilkan hasil 
u=[xg y y5];
figure(1)
imshow(u);
figure(2)
imshow(y);
figure(3)
imshow(y5);


