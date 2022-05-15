import sys, os


fl_headers = [os.path.splitext(x)[0] for x in os.listdir("src/") if ".h" in x]
fl_mdebug = [os.path.splitext(x)[0] for x in os.listdir("objmdebug/") if ".txt" in x]

# print(fl_headers)
# print(fl_mdebug)
print("remaining headers:")

for x in fl_mdebug:
    if x not in fl_headers:
        print("    %s"%x)