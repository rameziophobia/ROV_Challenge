#include "joystic_receive.h"

float Joystic_receive::maxVal(float a,float b)
{
    if(fabs(a) < fabs(b))
        return b;
    else
        return a;
}
float Joystic_receive::minVal(float a,float b)
{
    if(fabs(a) < fabs(b))
        return a;
    else
        return b;
}

Joystic_receive::Joystic_receive()
{
    //initiate receiver, then put received number in received

    x = x /32768.0 * 100;
    y = y /32768.0 * 100;
    z = z /32768.0 * 100;
    r = r /32768.0 * 100;
    x = 100; //For testing
    y = -100;
    z = 100;
    r = 0;

    if(fabs(x) == fabs(y) && fabs(y) == fabs(r))
    {
        PWMTR = (-x-y-r) / 3;
        PWMTL = (x-y+r) / 3;
        PWMBR = (x-y-r) / 3;
        PWMBL = (-x-y+r) / 3;
    }
    else if(x!=0 && y != 0 && r != 0 )
    {
        float TR,BL,BR,TL;
        float ratio = (minVal(fabs(x),fabs(y))/maxVal(fabs(x),fabs(y))), inv_ratio = 1-ratio;
        TR = (-minVal(ratio,inv_ratio) * minVal(x,y) - maxVal(ratio,inv_ratio) * maxVal(x,y));
        BL = (-minVal(ratio,inv_ratio) * minVal(x,y) - maxVal(ratio,inv_ratio) * maxVal(x,y));
        if(abs(x) < abs(y))
        {
            TL = (minVal(ratio,inv_ratio) * x - maxVal(ratio,inv_ratio) * y);
            BR = (minVal(ratio,inv_ratio) * x - maxVal(ratio,inv_ratio) * y);
        }
        else
        {
            TL = (maxVal(ratio,inv_ratio) * x - minVal(ratio,inv_ratio) * y);
            BR = (maxVal(ratio,inv_ratio) * x - minVal(ratio,inv_ratio) * y);
        }
        float ratioTR = (minVal(fabs(TR),fabs(r))/maxVal(fabs(TR),fabs(r))), inv_ratioTR = 1-ratioTR;
        float ratioTL = (minVal(fabs(TL),fabs(r))/maxVal(fabs(TL),fabs(r))), inv_ratioTL = 1-ratioTL;
        float ratioBR = (minVal(fabs(BR),fabs(r))/maxVal(fabs(BR),fabs(r))), inv_ratioBR = 1-ratioBR;
        float ratioBL = (minVal(fabs(BL),fabs(r))/maxVal(fabs(BL),fabs(r))), inv_ratioBL = 1-ratioBL;
        if(abs(TR) < abs(r))
        {
            PWMTR = (minVal(ratio,inv_ratioTR) * TR - maxVal(ratio,inv_ratioTR) * r);
        }
        else
        {
            PWMTR = (maxVal(ratio,inv_ratioTR) * TR - minVal(ratio,inv_ratioTR) * r);
        }
        if(abs(BR) < abs(r))
        {
            PWMBR = (minVal(ratio,inv_ratioBR) * BR - maxVal(ratio,inv_ratioBR) * r);
        }
        else
        {
            PWMBR = (maxVal(ratio,inv_ratioBR) * BR - minVal(ratio,inv_ratioBR) * r);
        }
        if(abs(TL) < abs(r))
        {
            PWMTL = (minVal(ratio,inv_ratioTL) * TL + maxVal(ratio,inv_ratioTL) * r);
        }
        else
        {
            PWMTL = (maxVal(ratio,inv_ratioTL) * TL + minVal(ratio,inv_ratioTL) * r);
        }
        if(abs(BL) < abs(r))
        {
            PWMBL = (minVal(ratio,inv_ratioBL) * BL + maxVal(ratio,inv_ratioBL) * r);
        }
        else
        {
            PWMBL = (maxVal(ratio,inv_ratioBL) * BL + minVal(ratio,inv_ratioBL) * r);
        }
    }
    else if(x!=0 && y != 0)
    {
        float ratio = minVal(fabs(x),fabs(y))/maxVal(fabs(x),fabs(y)), inv_ratio = 1-ratio;
        if(ratio == 1)
        {
            PWMTR = (-x-y-r) / 2;
            PWMTL = (x-y+r) / 2;
            PWMBR = (x-y-r) / 2;
            PWMBL = (-x-y+r) / 2;
        }
        else {
            PWMTR = (-minVal(ratio,inv_ratio) * minVal(x,y) - maxVal(ratio,inv_ratio) * maxVal(x,y));
            PWMBL = (-minVal(ratio,inv_ratio) * minVal(x,y) - maxVal(ratio,inv_ratio) * maxVal(x,y));
            if(abs(x) < abs(y))
            {
                qDebug() << ratio << "   " <<inv_ratio;
                PWMTL = (minVal(ratio,inv_ratio) * x - maxVal(ratio,inv_ratio) * y);
                PWMBR = (minVal(ratio,inv_ratio) * x - maxVal(ratio,inv_ratio) * y);
            }
            else
            {
                PWMTL = (maxVal(ratio,inv_ratio) * x - minVal(ratio,inv_ratio) * y);
                PWMBR = (maxVal(ratio,inv_ratio) * x - minVal(ratio,inv_ratio) * y);
            }
        }
    }
    else if(x!=0 && r != 0)
    {
        float ratio = (minVal(x,r)/maxVal(x,r)), inv_ratio = 1-ratio;
        if(ratio == 1)
        {
            PWMTR = (-x-y-r) / 2;
            PWMTL = (x-y+r) / 2;
            PWMBR = (x-y-r) / 2;
            PWMBL = (-x-y+r) / 2;
        }
        else
        {
            PWMTR = (-minVal(ratio,inv_ratio) * minVal(x,r) - maxVal(ratio,inv_ratio) * maxVal(x,r));
            PWMTL = (minVal(ratio,inv_ratio) * minVal(x,r) + maxVal(ratio,inv_ratio) * maxVal(x,r));
            if(abs(x) < abs(r))
            {
                PWMBL = (-minVal(ratio,inv_ratio) * x + maxVal(ratio,inv_ratio) * r);
                PWMBR = (minVal(ratio,inv_ratio) * x - maxVal(ratio,inv_ratio) * r);
            }
            else
            {
                PWMBL = (-maxVal(ratio,inv_ratio) * x + minVal(ratio,inv_ratio) * r);
                PWMBR = (maxVal(ratio,inv_ratio) * x - minVal(ratio,inv_ratio) * r);
            }
        }
    }
    else if(r!=0 && y != 0)
    {
        float ratio = (minVal(r,y)/maxVal(r,y)), inv_ratio = 1-ratio;
        if(ratio == 1)
        {
            PWMTR = (-x-y-r) / 2;
            PWMTL = (x-y+r) / 2;
            PWMBR = (x-y-r) / 2;
            PWMBL = (-x-y+r) / 2;
        }
        else{
            PWMTR = (-minVal(ratio,inv_ratio) * minVal(r,y) - maxVal(ratio,inv_ratio) * maxVal(r,y));
            PWMBR = (-minVal(ratio,inv_ratio) * minVal(r,y) - maxVal(ratio,inv_ratio) * maxVal(r,y));
            if(abs(x) < abs(y))
            {
                PWMTL = (minVal(ratio,inv_ratio) * r - maxVal(ratio,inv_ratio) * y);
                PWMBL = (minVal(ratio,inv_ratio) * r - maxVal(ratio,inv_ratio) * y);
            }
            else
            {
                PWMTL = (maxVal(ratio,inv_ratio) * r - minVal(ratio,inv_ratio) * y);
                PWMBL = (maxVal(ratio,inv_ratio) * r - minVal(ratio,inv_ratio) * y);
            }
        }
    }
    else
    {
        PWMTR = -x-y-r;
        PWMTL = x-y+r;
        PWMBR = x-y-r;
        PWMBL = -x-y+r;
    }
    if(z>0)
    {
        PWMT = z;
        PWMB = 0;
    }
    else if(z < 0)
    {
        PWMT = 0;
        PWMB = z;
    }
    else {
        PWMT = 0; PWMB = 0;
    }
    qDebug() << "     " << PWMT <<endl;
    qDebug() << PWMTL <<"         " <<PWMTR<<endl;
    qDebug() << PWMBL <<"         " <<PWMBR<<endl;
    qDebug() << "     " << PWMB <<endl;
    //Send PWM number to hat
}
