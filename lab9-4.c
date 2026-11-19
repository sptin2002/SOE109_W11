#include<stdio.h>

struct Employee{
    int idNum;
    double payRate;
    double hours;
};

double calcNet(struct Employee *);

int main(){
    struct Employee emp = {6768, 8.93, 40.5};
    double netpay;
    netpay = calcNet(&emp);
    printf("The net pay of employee %d is RMB %6.2f\n", emp.idNum, netpay);
    return 0;
}

double calcNet(struct Employee *temp){
    return (temp->payRate*temp->hours);
}