clc;
clear;
Ts=1;
fai=0.5;
xs=-1;
xf=1;
zs=-10;
h=2;

x=[];
z=[];

for t=0:0.01:Ts*fai
    signa=2*pi*t/(fai*Ts);
    xep=(xf-xs)*((signa-sin(signa))/(2*pi))+xs;
    zep=h*(1-cos(signa))/2+zs;
    x=[x,xep];
    z=[z,zep];
end
plot(x,z)