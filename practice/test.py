import sys
from practice import StringSet

class Tester:
    def __init__(self, num):
        self.num = num
        input_name = "s"+str(num)+".txt"
        with open(input_name, encoding='utf-8') as f:
            self.strset = StringSet([line.strip() for line in f.readlines()])
        
        self.samples = dict()
        test_name = "t"+str(num)+".txt"
        with open(test_name, encoding='utf-8') as f:
            lines = f.readlines()
            for line in lines:
                key, exists = line.strip().split()
                self.samples[key] = exists == '1'

    def test(self):
        success = True
        for key, exists in self.samples.items():
            if exists != self.strset.contains(key):
                success = False
                print("Failed: The \"" + key + "\" should " + ("NOT " if not exists else "") + "be contained!")
                
        return success

def test(num):
    if Tester(num).test():
        print("...OK")
    else:
        print("...Failed")

if __name__ == '__main__':
    argv = sys.argv
    if len(argv) == 1:
        # test for all
        for i in range(1, 5):
            print("Test" + str(i))
            test(i)
    else:
        test(int(argv[1]))
        
