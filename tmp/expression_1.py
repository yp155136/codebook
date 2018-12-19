#!usr/bin/env python3
#_*_coding:utf-8_*_
__author__='Byron Li'
import re
def calculate(formula):      #計算器主函數
    while True:
        if '(' in formula:
            inside_pare=re.search(r'\([^()]+\)',formula).group().strip('()')    #提取出一個最裏層括號的表達式，並將兩端號去除
            formula=re.sub(r'\([^()]+\)',four_opera(inside_pare),formula,1)      #計算去括號後表達式的四則運算，並將計算結果替換提取的包含括號的整個表達式
        else:
            return four_opera(formula)                                            #表達式中已不含括號，做四則運算得到最終計算結果

def four_opera(formula):     #無括號的加減乘除四則運算函數
    while True:
        if (re.search(r'[*/]',formula)):                                                                               #判斷表達式是否包含*、/運算符，乘除法優先計算
            formula_cell=re.search(r'(^\-?\d+\.?\d*|\d+\.?\d*)([*/])(\-?\d+\.?\d*)',formula).groups()              #提取出一個乘除計算單元，形如a*b或a/b，若計算單元在表達式開頭，左端數字為負數的話要匹配負號，若不在開頭左端數字只匹配數字不匹配符號。
            formula =re.sub(r'(^\-?\d+\.?\d*|\d+\.?\d*)([*/])(\-?\d+\.?\d*)', cal_cell(formula_cell), formula, 1)  #計算乘除法結果，並將結果替換提取到的乘除法計算單元
        elif re.search(r'(\-?\d+\.?\d*)([+-])(\-?\d+\.?\d*)', formula):                                             #表達式已不含乘除法，若能匹配出形如a+b或a-b加減法計算單元的，則進行加減法計算
            formula_cell=re.search(r'(\-?\d+\.?\d*)([+-])(\-?\d+\.?\d*)',formula).groups()                           #提取出形如a+b或a-b加減法計算單元
            formula =re.sub(r'(\-?\d+\.?\d*)([+-])(\-?\d+\.?\d*)', cal_cell(formula_cell), formula, 1)               #計算加減法結果，並將結果替換提取到的加減法計算單元
        else:
            return formula                                                                                             #表達式已不含乘除和加減法計算單元，即為四則運算的結果

def cal_cell(formula_cell):   #單個計算單元的計算函數，形如a+b,a-b,a*b,a/b的計算
    if formula_cell[1]=='+':
        return str(float(formula_cell[0])+float(formula_cell[2]))     #加法計算
    elif formula_cell[1]=='-':
        return str(float(formula_cell[0])-float(formula_cell[2]))     #減法計算
    elif formula_cell[1]=='*':
        return str(float(formula_cell[0])*float(formula_cell[2]))     #乘法計算
    else:
        return str(float(formula_cell[0])/float(formula_cell[2]))     #除法計算

if __name__=='__main__':
    while(True):
        formula=input("請輸入計算公式：")                            #輸入計算式
        # formula ='1 - 2 * ( (60-30 +(-40/5) * (9-2*5/3 + 7 /3*99/4*2998 +10 * 568/14 )) - (-4*3)/ (16-3*2) )'
        formula = ''.join(formula.split())
        if formula=='exit':break
        print('計算結果是：%s'%calculate(formula))                   #計算並打印結果
