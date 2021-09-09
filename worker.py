import os, sys
import re
import openpyxl
import multiprocessing
import logging
from openpyxl.cell.cell import Cell
from openpyxl.worksheet.worksheet import Worksheet
from openpyxl import utils

fmt_str = "%(asctime)s: %(levelname)s: %(funcName)s Line:%(lineno)d %(message)s"
date_str = "%d/%m/%Y %H:%M:%S"
logging.basicConfig(level=logging.DEBUG, format=fmt_str, datefmt=date_str)
logger = logging.getLogger(__name__)

# check if file exist
def check_file(file):
    if getattr(sys, 'frozen', False):
      application_path = os.path.dirname(sys.executable)
    elif __file__:
      application_path = os.path.dirname(__file__)
    file_path = os.path.abspath(os.path.join(application_path, file))
    if (os.path.exists(file_path)):
        return file_path
    else:
        logger.critical(f"File {file_path} is not existed")
        return None

def get_pics(input_str):
    return {}

def get_pixit(input_str):
    return {}

def get_testcase(ws:Worksheet, testcase_name):
    for row_cell in ws.iter_rows(ws.min_row, ws.max_row, utils.column_index_from_string("B"), utils.column_index_from_string("B")):
        if (row_cell[0].value == testcase_name):
            logger.debug(f"find {testcase_name} at {row_cell[0].coordinate}")
            # load config from F,G
            config = get_pics(ws.cell(row_cell[0].row, utils.column_index_from_string("F")))
            config.update(get_pixit(ws.cell(row_cell[0].row, utils.column_index_from_string("G"))))
            return (testcase_name, config)
    return ()

# find testcase
def get_excel_tc(file, testcase_name=None):
    # process all enable testcase in excel file
    logger.info(f"Processing {file} ...")
    wb = openpyxl.load_workbook(file, read_only=True)
    ws = wb["testcase"]
    # get all enable testcase
    if (testcase_name == None):
        pass
    else:
        pass



def main(argv):
    testcase_list = []
    excel_file = check_file("./testcase.xlsx")
    if (excel_file == None):
        return -1
    if len(argv) == 1:
        # execute all testcase in testcase.xlsx, get all testcase
        testcase_list = get_excel_tc(excel_file)
    else:
        # execute specific testcase as input
        testcase_list = get_excel_tc(excel_file, argv[1])

    # build

    # generate config for testcase

    # run testcase

    # update result to testcase_report.xlsx

    return 0

if __name__ == "__main__":
    exit(main(sys.argv))