with open("test.yaml", 'r') as conf:
    content = conf.readlines()

content = [x.rstrip("\n") for x in content if x.rstrip("\n")]

assert len(content)==31

tab = '  '

def resolveKeymap(mapName):
    return ""

def findKey(c):
    res = c.lstrip().split(':')[0]
    if not res:
        raise Exception('error')
    return res

def findVal(c):
    if len(c.lstrip().split(':')) > 1:
        return c.split(':')[1]
    return ""

def indentLevel(c):
    return (len(c) - len(c.lstrip())) / len(tab)

currentKey = list()  # ["sh", "ctrl", "c"]

previousVal = ""
result = dict()

for c in content:
    # if c.startswith('import:'):
    #     resolveKeymap(c.split(':')[1])
    # resolve and import keymaps
    print c
    k = findKey(c)  # shift
    indent_level = indentLevel(c)
    if len(currentKey) == indent_level and previousVal:
        raise Exception("previous value wrong" + c)
    if previousVal:
        result["".join(currentKey)] = previousVal
    currentKey = currentKey[:indent_level]
    currentKey.append(k)
    previousVal = findVal(c)

for key, value in result.iteritems():
    print key + ": " + value
