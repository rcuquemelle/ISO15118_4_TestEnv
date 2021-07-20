import os, sys, re, json, collections, enum, dataclasses, textwrap
from collections import namedtuple, defaultdict, Counter, OrderedDict, deque
from pdfminer.pdffont import main
import requests, bs4, lxml
from bs4 import BeautifulSoup
from io import StringIO
from pdfminer.converter import *
from pdfminer.layout import *
from pdfminer.pdfdocument import PDFDocument
from pdfminer.pdfinterp import PDFResourceManager, PDFPageInterpreter
from pdfminer.converter import PDFPageAggregator
from pdfminer.pdfpage import *
from pdfminer.pdfparser import PDFParser

# insert pdf path | src path | input msg name | page number from x-y
# read test case ID: test objective[1. CONDITION, 2. EXPECTED, 3. PICS, 4. PIXIT]
# insert to corresponding test case in file

@dataclasses.dataclass
class TestCase:
    id:str
    condition:str
    expected:str
    pics:str
    pixit:str
    
    def __repr__(self) -> str:
        cls = self.__class__.__name__
        return f"{cls}({id!r})"
    def __str__(self) -> str:
        return f"""
/**
1. CONDITION: {self.condition}
2. EXPECTED: {self.expected}
3. PICS selection: {self.pics}
4. PIXIT selection: {self.pixit}
*/
"""

def get_pdf_text(file_path, pageidx):
    retstr = StringIO()
    rsrcmgr = PDFResourceManager()
    laparams = LAParams()
    device = TextConverter(rsrcmgr, retstr, codec='utf-8', laparams=laparams)
    interpreter = PDFPageInterpreter(rsrcmgr, device)
    maxpages = pageidx.end
    pagenos=set([x for x in range(pageidx.start, pageidx.end)])

    fp = open(file_path, 'rb')
    for pnumber, page in enumerate(PDFPage.get_pages(fp, pagenos,
        maxpages=maxpages, password="",caching=True, check_extractable=True)):
        interpreter.process_page(page)
    if (retstr.seekable()):
        retstr.seek(0, os.SEEK_SET)

    msgname = r"TC_SECC_(DC|AC|CMN)_VTB_.*_\d+"
    check_point = [lambda input_str: "TC Id" in input_str,
                lambda input_str: re.match(msgname, input_str) != None,
                lambda input_str: "Test System executes" in input_str,
                lambda input_str: "Test System then checks" in input_str,
                lambda input_str: ("Document:" in input_str) or ("Document reference" in input_str),
                lambda input_str: ("PICS selection" in input_str) or ("PIXIT selection" in input_str),
                lambda input_str: ("f_SECC" in input_str) or ("PreCondition" in input_str)]

    check_idx = 0
    temp_var = None
    testcase_list = {}
    flag_cfg = ""
    cfg_done = 0
    for line in iter(retstr.readline, ''):
        line = re.sub(r"\t+"," ", line).strip()
        if (line != ""):
            if (check_point[check_idx](line)):
                if (check_idx == 5):
                    if ("PICS selection" in line):
                        flag_cfg = "PICS"
                        cfg_done += 1
                        if (cfg_done == 2):
                            check_idx += 1
                        continue
                    elif ("PIXIT selection" in line):
                        flag_cfg = "PIXIT"
                        cfg_done += 1
                        if (cfg_done == 2):
                            check_idx += 1
                        continue
                    else:
                        print(f"ERROR: {line}")
                else:
                    check_idx += 1
            if (check_idx == 0): # find TC Id
                continue
            # TC Id detect
            if (check_idx == 1): # find TC name
                temp_var = TestCase("", "", "", "", "")
                continue
            # msgname detect
            if (check_idx == 2): # find Condition
                if (temp_var.id == ""):
                    temp_var.id = line
                    continue
                else:
                    continue
            # condition detect
            if (check_idx == 3): # find expected
                if not (("All rights reserved" in line) or ("15118-4" in line)):
                    temp_var.condition += f" {line}"
                continue
            # expected detect
            if (check_idx == 4): # find end expected
                if not (("All rights reserved" in line) or ("15118-4" in line)):
                    temp_var.expected += f" {line}"
                continue
            # PICS
            if (check_idx in [5, 6]): # find PICS and PIXIT
                if (cfg_done != 0):
                    if (flag_cfg == "PICS"):
                        if not (("All rights reserved" in line) or ("15118-4" in line)):
                            temp_var.pics += line
                    elif (flag_cfg == "PIXIT"):
                        if not (("All rights reserved" in line) or ("15118-4" in line)):
                            temp_var.pixit += line
                continue
            # PIXIT
            if (check_idx == 7):
                check_idx = 0
                cfg_done = 0
                flag_cfg = ""
                print(temp_var.id)
                temp_var.condition = textwrap.fill(temp_var.condition.strip(), 80)
                temp_var.expected = textwrap.fill(temp_var.expected.strip(), 80)
                temp_var.pics = textwrap.fill(temp_var.pics.strip(), 80)
                temp_var.pixit = textwrap.fill(temp_var.pixit.strip(), 80)
                testcase_list.update({temp_var.id : temp_var})
    device.close()
    retstr.close()
    return testcase_list

if __name__ == "__main__":
    pdf_file = sys.argv[1]
    src_path = sys.argv[2]
    src_file_list = []
    for f in os.listdir(src_path):
        if (".cpp" in f):
            src_file_list.append(os.path.join(src_path, f))
    PageIndex = namedtuple("PageIndex", ["start", "end"])
    pageidx = PageIndex(245, 420)
    tc_list = get_pdf_text(pdf_file, pageidx)

    for f in src_file_list:
        msg_name =(os.path.split(f)[1])[10:-4]
        fp = open(f, "r", encoding="utf8")
        new_file = open(f.replace(".cpp", "_new.cpp"), "w", encoding="utf-8")
        # find "void TestCases_SECC_"line
        target_str = "void TestCases_SECC_" + msg_name
        for line in fp.readlines():
            if (target_str in line):
                robj = re.match(r"void .*::(.*)\(\)", line)
                if (robj != None):
                    msg = robj.group(1)
                    print(f"Update header: {msg}")
                    new_file.write(str(tc_list[msg]))
                    new_file.write(line)
                else:
                    print(f"Error: {line}")
            else:
                new_file.write(line)
        fp.close()
        new_file.close()
        os.remove(f)
        os.rename(new_file.name, f)