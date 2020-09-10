import requests
import os
import sys
from bs4 import BeautifulSoup

if os.path.isfile('response.txt'):
    os.remove('response.txt')

if __name__ == "__main__" :
    response = requests.get(sys.argv[1])
    print(response.raise_for_status())
    f = open('response.txt','wt')
    f.write('ok')
    f.close
