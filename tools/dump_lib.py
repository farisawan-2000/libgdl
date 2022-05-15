import sys, os

fn = "./libgdl_u64.a"

# check file exists
os.stat("%s" % fn)


os.system("ar x %s --output obj/" % fn)

flst = [os.path.splitext(x)[0] for x in os.listdir("obj/")]

# print(flst)

for i in flst:
    os.system("python3 tools/print_mdebug.py obj/%s.o > objmdebug/%s.txt" % (i,i))
    os.system("python3 tools/disassemble_elf.py obj/%s.o > objasm/%s.s" % (i,i))

