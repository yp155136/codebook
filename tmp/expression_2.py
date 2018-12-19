import re

def calculate(n1, n2, operator):

    '''
    :param n1: float
    :param n2: float
    :param operator: + - * /
    :return: float
    '''
    result = 0
    if operator == "+":
        result = n1 + n2
    if operator == "-":
        result = n1 - n2
    if operator == "*":
        result = n1 * n2
    if operator == "/":
        result = n1 / n2
    return result


# 判斷是否是運算符，如果是返回True
def is_operator(e):
    '''
    :param e: str
    :return: bool
    '''
    opers = ['+', '-', '*', '/', '(', ')']
    return True if e in opers else False


# 將算式處理成列表，解決橫槓是負數還是減號的問題
def formula_format(formula):
    # 去掉算式中的空格
    formula = re.sub(' ', '', formula)
    # 以 '橫槓數字' 分割， 其中正則表達式：(\-\d+\.?\d*) 括號內：
    # \- 表示匹配橫槓開頭； \d+ 表示匹配數字1次或多次；\.?表示匹配小數點0次或1次;\d*表示匹配數字1次或多次。
    formula_list = [i for i in re.split('(\-\d+\.?\d*)', formula) if i]

    # 最終的算式列表
    final_formula = []
    for item in formula_list:
        # 第一個是以橫槓開頭的數字（包括小數）final_formula。即第一個是負數，橫槓就不是減號
        if len(final_formula) == 0 and re.search('^\-\d+\.?\d*$', item):
            final_formula.append(item)
            continue

        if len(final_formula) > 0:
            # 如果final_formal最後一個元素是運算符['+', '-', '*', '/', '('], 則橫槓數字不是負數
            if re.search('[\+\-\*\/\(]$', final_formula[-1]):
                final_formula.append(item)
                continue
        # 按照運算符分割開
        item_split = [i for i in re.split('([\+\-\*\/\(\)])', item) if i]
        final_formula += item_split
    return final_formula


def decision(tail_op, now_op):
    '''
    :param tail_op: 運算符棧的最後一個運算符
    :param now_op: 從算式列表取出的當前運算符
    :return: 1 代表彈棧運算，0 代表彈運算符棧最後一個元素， -1 表示入棧
    '''
    # 定義4種運算符級別
    rate1 = ['+', '-']
    rate2 = ['*', '/']
    rate3 = ['(']
    rate4 = [')']

    if tail_op in rate1:
        if now_op in rate2 or now_op in rate3:
            # 説明連續兩個運算優先級不一樣，需要入棧
            return -1
        else:
            return 1

    elif tail_op in rate2:
        if now_op in rate3:
            return -1
        else:
            return 1

    elif tail_op in rate3:
        if now_op in rate4:
            return 0   # ( 遇上 ) 需要彈出 (，丟掉 )
        else:
            return -1  # 只要棧頂元素為(，當前元素不是)都應入棧。
    else:
        return -1


def final_calc(formula_list):
    num_stack = []       # 數字棧
    op_stack = []        # 運算符棧
    for e in formula_list:
        operator = is_operator(e)
        if not operator:
            # 壓入數字棧
            # 字符串轉換為符點數
            num_stack.append(float(e))
        else:
            # 如果是運算符
            while True:
                # 如果運算符棧等於0無條件入棧
                if len(op_stack) == 0:
                    op_stack.append(e)
                    break

                # decision 函數做決策
                tag = decision(op_stack[-1], e)
                if tag == -1:
                    # 如果是-1壓入運算符棧進入下一次循環
                    op_stack.append(e)
                    break
                elif tag == 0:
                    # 如果是0彈出運算符棧內最後一個(, 丟掉當前)，進入下一次循環
                    op_stack.pop()
                    break
                elif tag == 1:
                    # 如果是1彈出運算符棧內最後兩個元素，彈出數字棧最後兩比特素。
                    op = op_stack.pop()
                    num2 = num_stack.pop()
                    num1 = num_stack.pop()
                    # 執行計算
                    # 計算之後壓入數字棧
                    num_stack.append(calculate(num1, num2, op))
    # 處理大循環結束後 數字棧和運算符棧中可能還有元素 的情況
    while len(op_stack) != 0:
        op = op_stack.pop()
        num2 = num_stack.pop()
        num1 = num_stack.pop()
        num_stack.append(calculate(num1, num2, op))

    return num_stack, op_stack

if __name__ == '__main__':
    #formula = "8+9+17-0+101-48"
    #print("算式：", formula)
    xx = input();
    formula = ""
    for i in xx:
        if i != '=' :
            formula = formula + str(i)
    formula_list = formula_format(formula)
    result, _ = final_calc(formula_list)
    print(int(result[0]))
    #print("計算結果：", result[0])

# 算式： 1 - 2 * ( (60-30 +(-40/5) * (9-2*5/3 + 7 /3*99/4*2998 +10 * 568/14 )) - (-4*3)/ (16-3*2))
# 計算結果： 2776672.6952380957
