#!/usr/bin/env python
# -*- coding: utf-8 -*-

# 参考: taichino.com さん
# - http://taichino.com/programming/1057

import urllib
import urllib2
from oauth import oauth

# ユーザ登録時にもらえる情報
consumer_key = 'XXXXXXXXXXXXXXXXXXXXXXXX'
secret_key = 'XXXXXXXXXXXXXXXXXXXXXXXX'

# リクエストしたいURLとパラメータ
url = 'http://gdd-2010-quiz-japan.appspot.com/oauth/XXXXXXXXXXXXXXXXXXXXXXXX'
params = {
  'hello' : 'world'
}

# 1. Consumerオブジェクト作成
consumer = oauth.OAuthConsumer(consumer_key, secret_key)
# 2. HTTPリクエスト組み立て
request  = oauth.OAuthRequest.from_consumer_and_token(consumer, http_method='POST', http_url=url, parameters=params)
# 3. リクエストに署名して発行
request.sign_request(oauth.OAuthSignatureMethod_HMAC_SHA1(), consumer, None)
header = request.to_header('devquiz')
req = urllib2.Request(url, request.to_postdata())
req.add_header('Authorization', header['Authorization'])
stream = urllib2.urlopen(req)
print stream.read()
