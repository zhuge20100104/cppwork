#ifndef _FREDRIC_REF_DEMO_H_
#define _FREDRIC_REF_DEMO_H_

struct RefDemo
{
    int val {10};
    int &x  = val;
};


void assign_ref(RefDemo& rf);

#endif