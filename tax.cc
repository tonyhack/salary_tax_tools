#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const double kSocialInsuranceBaseMin = 4297.0f;
    const double kSocialInsuranceBaseMax = 21396.0f;
    const double kSocialInsurancePersonalPaymentPercent = 10.5f;
    const double kHousingFundBaseMin = 2300.0f;
    const double kHousingFundBaseMax = 21400.0f;
    const double kHousingFundPersonalPaymentPercent = 7.0f;

    double salary = 0.0f;
    double housing_fund_personal_payment_percent = 0.0f;
    double salary_tax_base = 3500.0f;

    if (argc == 1) {
        printf("invalid param.\n");
        printf("param: <月薪> [个税起征点(默认值为3500)] [补充公积金百分比(默认值为0)]\n");
        return 0;
    }

    if (argc > 2) {
        salary_tax_base = atof(argv[2]);
    }

    if (argc > 3)
    {
        housing_fund_personal_payment_percent = atof(argv[3]);
    }

    salary = atof(argv[1]);

    double social_insurance_base = salary;
    double housing_fund_base = salary;

    if (social_insurance_base < kSocialInsuranceBaseMin) {
        social_insurance_base = kSocialInsuranceBaseMin;
    }
    else if (social_insurance_base > kSocialInsuranceBaseMax) {
        social_insurance_base = kSocialInsuranceBaseMax;
    }

    if (housing_fund_base < kHousingFundBaseMin) {
        housing_fund_base = kHousingFundBaseMin;
    }
    else if (housing_fund_base > kHousingFundBaseMax) {
        housing_fund_base = kHousingFundBaseMax;
    }

    double social_insurance_payment =
        social_insurance_base * kSocialInsurancePersonalPaymentPercent / 100.0f;
    double housing_fund_payment =
        housing_fund_base * kHousingFundPersonalPaymentPercent / 100.0f +
        housing_fund_base * housing_fund_personal_payment_percent / 100.0f;

    double salary_without_payment = salary - social_insurance_payment - housing_fund_payment;
    double tax = 0.0f;

    do {
        if (salary_without_payment <= salary_tax_base) {
            break;
        }

        double salary_need_pay_tax = salary_without_payment - salary_tax_base;
        if (salary_need_pay_tax <= 1500) {
            tax = salary_need_pay_tax * 3.0f / 100.0f;
        }
        else if (salary_need_pay_tax <= 4500) {
            tax = salary_need_pay_tax * 10.0f / 100.0f - 105;
        }
        else if (salary_need_pay_tax <= 9000) {
            tax = salary_need_pay_tax * 20.0f / 100.0f - 555;
        }
        else if (salary_need_pay_tax <= 35000) {
            tax = salary_need_pay_tax * 25.0f / 100.0f - 1005;
        }
        else if (salary_need_pay_tax <= 55000) {
            tax = salary_need_pay_tax * 30.0f / 100.0f - 2755;
        }
        else if (salary_need_pay_tax <= 80000) {
            tax = salary_need_pay_tax * 35.0f / 100.0f - 5505;
        }
        else {
            tax = salary_need_pay_tax * 45.0f / 100.0f - 13505;
        }
    } while (false);

    printf("        税前: %f        到手: %f\n",
            salary, salary_without_payment - tax);
    printf("        社保基数: %f    社保支出: %f\n", social_insurance_base,
            social_insurance_payment);
    printf("        公积金基数: %f  公积金百分比: %f%    公积金支出: %f\n",
            housing_fund_base, kHousingFundPersonalPaymentPercent + housing_fund_personal_payment_percent, housing_fund_payment);
    printf("        个税支出: %f\n", tax);

    return 0;
}
