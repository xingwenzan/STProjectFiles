clc;
clear;
Ts=1;
fai=0.5;
xs=-1;
xf=1;
zs=-10;
h=1;
L1=8;
L2=6.15;


for t=0:0.01:Ts
    if t<=Ts*fai
        signa=2*pi*t/(fai*Ts);
        xep0=(xf-xs)*((signa-sin(signa))/(2*pi))+xs;
        zep0=h*(1-cos(signa))/2+zs;    
    else
        signa=2*pi*(t-Ts*fai)/(fai*Ts);
        zep0=-10;
        xep0=(xs-xf)*((signa-sin(signa))/(2*pi))+xf;
    end

    [S,G]=KinematicsInverseSolution(-xep0,-zep0,L1,L2);
    G=G+pi;
    xep1=L1*cos(G);
    zep1=L1*sin(G);
    
    S=S+G;
    xep2=xep1+L2*cos(S);
    zep2=zep1+L2*sin(S);

    line([0,xep1],[0,zep1]);
    line([xep1,xep0],[zep1,zep0],'color','y');
    line([xep1,xep2],[zep1,zep2],'color','r');
end
%plot(x_foot,z_foot)


function [thetaS,thetaG] = KinematicsInverseSolution(x,y,l1,l2)
thetaS=pi-acos((x*x+y*y-l1*l1-l2*l2)/(-2*l1*l2));
fail=acos((l1*l1+x*x+y*y-l2*l2)/(2*l1*sqrt(x*x+y*y)));
if x>0
    thetaG=abs(atan(y/x))-fail;
elseif x<0
    thetaG=pi-abs(atan(y/x))-fail;
else
    thetaG=pi/2-fail;
end
end