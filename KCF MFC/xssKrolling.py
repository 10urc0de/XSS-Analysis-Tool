import requests
from bs4 import BeautifulSoup

if os.path.isfile('xssKrolling.txt'):
    os.remove('xssKrolling.txt')
    
res = requests.get('https://gist.githubusercontent.com/kurobeats/9a613c9ab68914312cbb415134795b45/raw/0cabac66ba1afe03c17a72a3ca6c66b0666457b8/xss_vectors.txt')

data = res.content
print(data)
f = open("xssKrolling.txt","wb")
f.write(data)
f.close
