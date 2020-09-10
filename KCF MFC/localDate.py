import requests
from bs4 import BeautifulSoup

if os.path.isfile('localDate.txt'):
    os.remove('localDate.txt')
    
# 1) reqeusts 라이브러리를 활용한 HTML 페이지 요청 
# 1-1) res 객체에 HTML 데이터가 저장되고, res.content로 데이터를 추출할 수 있음
res = requests.get('https://gist.github.com/kurobeats/9a613c9ab68914312cbb415134795b45')

# print(res.content)
# 2) HTML 페이지 파싱 BeautifulSoup(HTML데이터, 파싱방법)
# 2-1) BeautifulSoup 파싱방법
soup = BeautifulSoup(res.content, 'html.parser')

# 3) 필요한 데이터 검색
data = soup.find('time-ago',{'class': 'no-wrap'})

# 4) 필요한 데이터 추출
f = open('localDate.txt','w')
f.write(data.get_text())
f.close()
