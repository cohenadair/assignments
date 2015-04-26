from bottle import route, run, request
import json
import os

"""
curl -X PUT -d key=value -d key2=value2 localhost:8080/tokens/
curl -X GET localhost:8080/tokens/

"""

boardTokens = {'0' : '', '1' : '', '2' : '', '3' : '', '4' : '', '5' : '', '6' : '', '7' : '', '8' : ''}
X = "X"
O = "O"
isXAssigned = False
isOAssigned = False


@route('/')
def home():
    return "home"


@route('/tokens/put/', method = 'POST')
def tokens_put():
    key = request.forms.get("key")
    value = request.forms.get("value")
    boardTokens[key] = value;
    return { "success" : True }


@route('/tokens/get/', method = 'GET')
def tokens_get():
    return boardTokens


@route('/available_token/', method = "GET")
def available_token():
    result = ""
    global isXAssigned, isOAssigned
    
    if not isXAssigned:
        isXAssigned = True
        result = X
    elif not isOAssigned:
        isOAssigned = True
        result = O
        
    return { "token" : result }


@route('/get_winner/', method = "GET")
def get_winner():
    result = ""
    T = boardTokens

    if T['0'] == T['1'] and T['1'] == T['2'] and T['0'] != '':
        result = T['0']
    if T['3'] == T['4'] and T['4'] == T['5'] and T['3'] != '':
        result = T['3']
    if T['6'] == T['7'] and T['7'] == T['8'] and T['6'] != '':
        result = T['6']
    if T['0'] == T['3'] and T['3'] == T['6'] and T['0'] != '':
        result = T['0']
    if T['1'] == T['4'] and T['4'] == T['7'] and T['1'] != '':
        result = T['1']
    if T['2'] == T['5'] and T['5'] == T['8'] and T['2'] != '':
        result = T['2']
    if T['0'] == T['4'] and T['4'] == T['8'] and T['0'] != '':
        result = T['0']
    if T['2'] == T['4'] and T['4'] == T['6'] and T['2'] != '':
        result = T['2']

    # check for tie
    if len(result) == 0:
        tie = True
        for key in boardTokens:
            if boardTokens[key] == '':
                tie = False                
                break
        if tie:
            result = "None"

    return { "winner" : result }


run(host='localhost', port=8080, debug=True)
