t = int(input())
while t > 0:
    x = int(input())
    a = b = c = 0
    if x % 2 == 0:
        a = b = c = x//2
    elif x % 11 != 10:
        a = x//11
        b = x-a
        if a == 0:
            c = "-"
        else:
            c = a
    else:
        rest = x % 100
        if rest not in [19,39,59,79,99]:
            a = x//2
            b = a+1
            c = a//10
        else:
            nr9 = 0
            while x % 200 == 199:
                x //= 10
                nr9 += 1
            rest = x % 200
            aux = str(x//200)
            c1 = c2 = ""
            c3 = 0
            if rest == 19:
                a = aux + "09"
                b = aux + "10"
                c = aux + "0"
                c1 = "0"
                c2 = "9"
                c3 = 2
            elif rest == 39:
                a = aux + "18"
                b = aux + "21"
                c = aux + "1"
                c1 = "1"
                c2 = "8"
                c3 = 2
            elif rest == 59:
                a = aux + "27"
                b = aux + "32"
                c = aux + "2"
                c1 = "2"
                c2 = "7"
                c3 = 2
            elif rest == 79:
                a = aux + "36"
                b = aux + "43"
                c = aux + "3"
                c1 = "3"
                c2 = "6"
                c3 = 2
            elif rest == 99:
                a = aux + "45"
                b = aux + "54"
                c = aux + "4"
                c1 = "4"
                c2 = "5"
                c3 = 2
            elif rest == 119:
                a = aux + "63"
                b = aux + "56"
                c = aux + "6"
                c1 = "6"
                c2 = "3"
                c3 = 2
            elif rest == 139:
                a = aux + "72"
                b = aux + "67"
                c = aux + "7"
                c1 = "7"
                c2 = "2"
                c3 = 2
            elif rest == 159:
                a = aux + "81"
                b = aux + "78"
                c = aux + "8"
                c1 = "8"
                c2 = "1"
                c3 = 2
            elif rest == 179:
                a = aux + "89"
                b = aux + "90"
                c = aux + "9"
                c1 = "0"
                c2 = "9"
                c3 = 1

            for i in range(nr9):
                if i % 2 == 0:
                    a += c1
                    b += c2
                    if c3 == 1:
                        c += c1
                    else:
                        c += c2
                else:
                    a += c2
                    b += c1
                    if c3 == 1:
                        c += c2
                    else:
                        c += c1
    print(a)
    print(b)
    print(c)
    t -= 1