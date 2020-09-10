import requests
import sys
    
ID = sys.argv[1]
PW = sys.argv[2]
Script = sys.argv[3]
LoginURL = sys.argv[4]
bbsURL = sys.argv[5]
number = sys.argv[6]
URL = sys.argv[7]

#로그인 유저 정보
LOGIN_INFO = {
    'userID': ID,
    'userPassword': PW
}

BBS_INFO = {
    'bbsTitle': number,
    'bbsContent': Script
}

#로그인 후 쿠키값 받아오기

s =  requests.Session()
login_req = s.post(LoginURL, data=LOGIN_INFO)
print(login_req.status_code)
print(login_req.cookies.get_dict())

#게시글 작성
r = s.post(bbsURL,data=BBS_INFO)
print(r.status_code)

view = s.post(URL)

f = open("Content.txt","w")
f.write(view.text)
f.close
