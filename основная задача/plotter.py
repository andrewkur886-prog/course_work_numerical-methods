import matplotlib.pyplot as plt
import os

schet=0




f=open(r'F:\уник\дз по пиая\2 kurs 4 semestr\ch meth kursovaya runge kutta 12\ch meth kursovaya runge kutta 12\out.txt')
for a in range(30):
    lines=[]
    for i in range(15005):
        lines.append(f.readline())  

# with open(r'F:\уник\дз по пиая\2 kurs 4 semestr\ch meth kursovaya runge kutta 12\ch meth kursovaya runge kutta 12\out.txt') as f:
#     for i in range(153):
#         lines.append(f.readline())   


# print(lines)

    t=[]
    x=[]
    y=[]
    lines.pop()
    lines.pop()
    str_alpha=lines[0].strip()
    lines.pop(0)
    lines.pop(0)

    for line in lines:
        line=line.strip()
        parts=line.split()
        t.append(float(parts[0]))
        x.append(float(parts[1]))
        y.append(float(parts[2]))


# print(t)

    directory_path=r'F:\уник\дз по пиая\2 kurs 4 semestr\ch meth kursovaya runge kutta 12\графики'
    plt.title(f"Популяция жертв X(t) в зависимости от t, alpha={a+1}")
    plt.plot(t, x, label='x', color='red')
    plt.xlabel("t")
    plt.ylabel("X(t)")


    plt.grid(
        color='gray', 
        linestyle='--',
        linewidth=0.5,
        alpha=0.7
    )   

    ax = plt.gca()
    # ax.spines['bottom'].set_position('zero') 
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')

    plot_name=f'plot_{str_alpha}_{str(schet)}.png'
    schet+=1
    plot_path= os.path.join(directory_path, plot_name)
    plt.savefig(plot_path, format='png')
    plt.clf()


    plt.title(f"Популяция хищников Y(t) в зависимости от t, alpha={a+1}")
    plt.plot(t, y, label='y', color='blue')
    plt.xlabel("t")
    plt.ylabel("Y(t)")

    plt.grid(
    color='gray', 
    linestyle='--',
    linewidth=0.5,
    alpha=0.7
    )

    ax = plt.gca()
    # ax.spines['bottom'].set_position('zero') 
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')

    plot_name=f'plot_{str_alpha}_{str(schet)}.png'
    schet+=1
    plot_path= os.path.join(directory_path, plot_name)
    plt.savefig(plot_path, format='png')
    plt.clf()



    plt.title(f"Популяция хищников Y(t) в зависимости от X(t), alpha={a+1}")
    plt.plot(x, y, label='x y', color='black')
    plt.ylabel("Y(t)")
    plt.xlabel("X(t)")

    plt.grid(
        color='gray', 
        linestyle='--',
        linewidth=0.5,
        alpha=0.7
    )

    ax = plt.gca()
    # ax.spines['bottom'].set_position('zero') 
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    plot_name=f'plot_{str_alpha}_{str(schet)}.png'
    plot_path= os.path.join(directory_path, plot_name)
    plt.savefig(plot_path, format='png')
    plt.clf()
    schet+=1


f.close()
#0.5 0.5 ghb alpha 2 4 6
#1 0.7 
#0.7 1