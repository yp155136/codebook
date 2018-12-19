#!usr/bin/env python3
#_*_coding:utf-8_*_
__author__='Byron Li'
import re
def calculate(formula):      #�p�⾹�D���
    while True:
        if '(' in formula:
            inside_pare=re.search(r'\([^()]+\)',formula).group().strip('()')    #�����X�@�ӳ��ؼh�A������F���A�ñN��ݸ��h��
            formula=re.sub(r'\([^()]+\)',four_opera(inside_pare),formula,1)      #�p��h�A�����F�����|�h�B��A�ñN�p�⵲�G�����������]�t�A������Ӫ�F��
        else:
            return four_opera(formula)                                            #��F�����w���t�A���A���|�h�B��o��̲׭p�⵲�G

def four_opera(formula):     #�L�A�����[����|�h�B����
    while True:
        if (re.search(r'[*/]',formula)):                                                                               #�P�_��F���O�_�]�t*�B/�B��šA�����k�u���p��
            formula_cell=re.search(r'(^\-?\d+\.?\d*|\d+\.?\d*)([*/])(\-?\d+\.?\d*)',formula).groups()              #�����X�@�ӭ����p��椸�A�Φpa*b��a/b�A�Y�p��椸�b��F���}�Y�A���ݼƦr���t�ƪ��ܭn�ǰt�t���A�Y���b�}�Y���ݼƦr�u�ǰt�Ʀr���ǰt�Ÿ��C
            formula =re.sub(r'(^\-?\d+\.?\d*|\d+\.?\d*)([*/])(\-?\d+\.?\d*)', cal_cell(formula_cell), formula, 1)  #�p�⭼���k���G�A�ñN���G���������쪺�����k�p��椸
        elif re.search(r'(\-?\d+\.?\d*)([+-])(\-?\d+\.?\d*)', formula):                                             #��F���w���t�����k�A�Y��ǰt�X�Φpa+b��a-b�[��k�p��椸���A�h�i��[��k�p��
            formula_cell=re.search(r'(\-?\d+\.?\d*)([+-])(\-?\d+\.?\d*)',formula).groups()                           #�����X�Φpa+b��a-b�[��k�p��椸
            formula =re.sub(r'(\-?\d+\.?\d*)([+-])(\-?\d+\.?\d*)', cal_cell(formula_cell), formula, 1)               #�p��[��k���G�A�ñN���G���������쪺�[��k�p��椸
        else:
            return formula                                                                                             #��F���w���t�����M�[��k�p��椸�A�Y���|�h�B�⪺���G

def cal_cell(formula_cell):   #��ӭp��椸���p���ơA�Φpa+b,a-b,a*b,a/b���p��
    if formula_cell[1]=='+':
        return str(float(formula_cell[0])+float(formula_cell[2]))     #�[�k�p��
    elif formula_cell[1]=='-':
        return str(float(formula_cell[0])-float(formula_cell[2]))     #��k�p��
    elif formula_cell[1]=='*':
        return str(float(formula_cell[0])*float(formula_cell[2]))     #���k�p��
    else:
        return str(float(formula_cell[0])/float(formula_cell[2]))     #���k�p��

if __name__=='__main__':
    while(True):
        formula=input("�п�J�p�⤽���G")                            #��J�p�⦡
        # formula ='1 - 2 * ( (60-30 +(-40/5) * (9-2*5/3 + 7 /3*99/4*2998 +10 * 568/14 )) - (-4*3)/ (16-3*2) )'
        formula = ''.join(formula.split())
        if formula=='exit':break
        print('�p�⵲�G�O�G%s'%calculate(formula))                   #�p��å��L���G
