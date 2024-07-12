from fastapi import FastAPI
import bs4 as bs
import requests

app = FastAPI()

URL = 'http://www.cbr.ru/scripts/XML_daily.asp'

st='''
<?xml version="1.0" encoding="windows-1251"?><ValCurs Date="30.03.2024" name="Foreign Currency Market"><Valute ID="R01010"><NumCode>036</NumCode><CharCode>AUD</CharCode><Nominal>1</Nominal><Name> </Name><Value>60,3335</Value><VunitRate>60,3335</VunitRate></Valute><Valute ID="R01020A"><NumCode>944</NumCode><CharCode>AZN</CharCode><Nominal>1</Nominal><Name> </Name><Value>54,3329</Value><VunitRate>54,3329</VunitRate></Valute><Valute ID="R01035"><NumCode>826</NumCode><CharCode>GBP</CharCode><Nominal>1</Nominal><Name>   </Name><Value>116,6490</Value><VunitRate>116,649</VunitRate></Valute><Valute ID="R01060"><NumCode>051</NumCode><CharCode>AMD</CharCode><Nominal>100</Nominal><Name> </Name><Value>23,4861</Value><VunitRate>0,234861</VunitRate></Valute><Valute ID="R01090B"><NumCode>933</NumCode><CharCode>BYN</CharCode><Nominal>1</Nominal><Name> </Name><Value>28,4002</Value><VunitRate>28,4002</VunitRate></Valute><Valute ID="R01100"><NumCode>975</NumCode><CharCode>BGN</CharCode><Nominal>1</Nominal><Name> </Name><Value>51,0560</Value><VunitRate>51,056</VunitRate></Valute><Valute ID="R01115"><NumCode>986</NumCode><CharCode>BRL</CharCode><Nominal>1</Nominal><Name> </Name><Value>18,4884</Value><VunitRate>18,4884</VunitRate></Valute><Valute ID="R01135"><NumCode>348</NumCode><CharCode>HUF</CharCode><Nominal>100</Nominal><Name> </Name><Value>25,1452</Value><VunitRate>0,251452</VunitRate></Valute><Valute ID="R01150"><NumCode>704</NumCode><CharCode>VND</CharCode><Nominal>10000</Nominal><Name> </Name><Value>38,4810</Value><VunitRate>0,0038481</VunitRate></Valute><Valute ID="R01200"><NumCode>344</NumCode><CharCode>HKD</CharCode><Nominal>1</Nominal><Name> </Name><Value>11,8236</Value><VunitRate>11,8236</VunitRate></Valute><Valute ID="R01210"><NumCode>981</NumCode><CharCode>GEL</CharCode><Nominal>1</Nominal><Name> </Name><Value>34,2375</Value><VunitRate>34,2375</VunitRate></Valute><Valute ID="R01215"><NumCode>208</NumCode><CharCode>DKK</CharCode><Nominal>1</Nominal><Name> </Name><Value>13,3951</Value><VunitRate>13,3951</VunitRate></Valute><Valute ID="R01230"><NumCode>784</NumCode><CharCode>AED</CharCode><Nominal>1</Nominal><Name> </Name><Value>25,1507</Value><VunitRate>25,1507</VunitRate></Valute><Valute ID="R01235"><NumCode>840</NumCode><CharCode>USD</CharCode><Nominal>1</Nominal><Name> </Name><Value>92,3660</Value><VunitRate>92,366</VunitRate></Valute><Valute ID="R01239"><NumCode>978</NumCode><CharCode>EUR</CharCode><Nominal>1</Nominal><Name></Name><Value>99,5299</Value><VunitRate>99,5299</VunitRate></Valute><Valute ID="R01240"><NumCode>818</NumCode><CharCode>EGP</CharCode><Nominal>10</Nominal><Name> </Name><Value>19,4877</Value><VunitRate>1,94877</VunitRate></Valute><Valute ID="R01270"><NumCode>356</NumCode><CharCode>INR</CharCode><Nominal>10</Nominal><Name> </Name><Value>11,0785</Value><VunitRate>1,10785</VunitRate></Valute><Valute ID="R01280"><NumCode>360</NumCode><CharCode>IDR</CharCode><Nominal>10000</Nominal><Name> </Name><Value>58,2641</Value><VunitRate>0,00582641</VunitRate></Valute><Valute ID="R01335"><NumCode>398</NumCode><CharCode>KZT</CharCode><Nominal>100</Nominal><Name> </Name><Value>20,6105</Value><VunitRate>0,206105</VunitRate></Valute><Valute ID="R01350"><NumCode>124</NumCode><CharCode>CAD</CharCode><Nominal>1</Nominal><Name> </Name><Value>68,1668</Value><VunitRate>68,1668</VunitRate></Valute><Valute ID="R01355"><NumCode>634</NumCode><CharCode>QAR</CharCode><Nominal>1</Nominal><Name> </Name><Value>25,3753</Value><VunitRate>25,3753</VunitRate></Valute><Valute ID="R01370"><NumCode>417</NumCode><CharCode>KGS</CharCode><Nominal>10</Nominal><Name> </Name><Value>10,3236</Value><VunitRate>1,03236</VunitRate></Valute><Valute ID="R01375"><NumCode>156</NumCode><CharCode>CNY</CharCode><Nominal>1</Nominal><Name> </Name><Value>12,6710</Value><VunitRate>12,671</VunitRate></Valute><Valute ID="R01500"><NumCode>498</NumCode><CharCode>MDL</CharCode><Nominal>10</Nominal><Name> </Name><Value>52,3471</Value><VunitRate>5,23471</VunitRate></Valute><Valute ID="R01530"><NumCode>554</NumCode><CharCode>NZD</CharCode><Nominal>1</Nominal><Name> </Name><Value>55,3365</Value><VunitRate>55,3365</VunitRate></Valute><Valute ID="R01535"><NumCode>578</NumCode><CharCode>NOK</CharCode><Nominal>10</Nominal><Name> </Name><Value>85,5154</Value><VunitRate>8,55154</VunitRate></Valute><Valute ID="R01565"><NumCode>985</NumCode><CharCode>PLN</CharCode><Nominal>1</Nominal><Name> </Name><Value>23,1575</Value><VunitRate>23,1575</VunitRate></Valute><Valute ID="R01585F"><NumCode>946</NumCode><CharCode>RON</CharCode><Nominal>1</Nominal><Name> </Name><Value>20,0456</Value><VunitRate>20,0456</VunitRate></Valute><Valute ID="R01589"><NumCode>960</NumCode><CharCode>XDR</CharCode><Nominal>1</Nominal><Name> (  )</Name><Value>122,2399</Value><VunitRate>122,2399</VunitRate></Valute><Valute ID="R01625"><NumCode>702</NumCode><CharCode>SGD</CharCode><Nominal>1</Nominal><Name> </Name><Value>68,5411</Value><VunitRate>68,5411</VunitRate></Valute><Valute ID="R01670"><NumCode>972</NumCode><CharCode>TJS</CharCode><Nominal>10</Nominal><Name> </Name><Value>84,3440</Value><VunitRate>8,4344</VunitRate></Valute><Valute ID="R01675"><NumCode>764</NumCode><CharCode>THB</CharCode><Nominal>10</Nominal><Name> </Name><Value>25,3405</Value><VunitRate>2,53405</VunitRate></Valute><Valute ID="R01700J"><NumCode>949</NumCode><CharCode>TRY</CharCode><Nominal>10</Nominal><Name> </Name><Value>28,6063</Value><VunitRate>2,86063</VunitRate></Valute><Valute ID="R01710A"><NumCode>934</NumCode><CharCode>TMT</CharCode><Nominal>1</Nominal><Name>  </Name><Value>26,3903</Value><VunitRate>26,3903</VunitRate></Valute><Valute ID="R01717"><NumCode>860</NumCode><CharCode>UZS</CharCode><Nominal>10000</Nominal><Name> </Name><Value>73,1897</Value><VunitRate>0,00731897</VunitRate></Valute><Valute ID="R01720"><NumCode>980</NumCode><CharCode>UAH</CharCode><Nominal>10</Nominal><Name> </Name><Value>23,5499</Value><VunitRate>2,35499</VunitRate></Valute><Valute ID="R01760"><NumCode>203</NumCode><CharCode>CZK</CharCode><Nominal>10</Nominal><Name> </Name><Value>39,4507</Value><VunitRate>3,94507</VunitRate></Valute><Valute ID="R01770"><NumCode>752</NumCode><CharCode>SEK</CharCode><Nominal>10</Nominal><Name> </Name><Value>86,6437</Value><VunitRate>8,66437</VunitRate></Valute><Valute ID="R01775"><NumCode>756</NumCode><CharCode>CHF</CharCode><Nominal>1</Nominal><Name> </Name><Value>101,9267</Value><VunitRate>101,9267</VunitRate></Valute><Valute ID="R01805F"><NumCode>941</NumCode><CharCode>RSD</CharCode><Nominal>100</Nominal><Name> </Name><Value>84,9845</Value><VunitRate>0,849845</VunitRate></Valute><Valute ID="R01810"><NumCode>710</NumCode><CharCode>ZAR</CharCode><Nominal>10</Nominal><Name> </Name><Value>48,6326</Value><VunitRate>4,86326</VunitRate></Valute><Valute ID="R01815"><NumCode>410</NumCode><CharCode>KRW</CharCode><Nominal>1000</Nominal><Name>  </Name><Value>68,5615</Value><VunitRate>0,0685615</VunitRate></Valute><Valute ID="R01820"><NumCode>392</NumCode><CharCode>JPY</CharCode><Nominal>100</Nominal><Name> </Name><Value>61,0684</Value><VunitRate>0,610684</VunitRate></Valute></ValCurs>%

'''


def get_rate(code: str):
    resp = requests.get(URL).text

    soup = bs.BeautifulSoup(st, "xml")
    rate_values = soup.find_all('Value')

    chars = soup.find_all('CharCode')
    chars = list(map(lambda x: x.text, chars))
    rate_values = list(map(lambda x: x.text, rate_values))

    for rate_currency in rate_values:
        if chars[rate_values.index(rate_currency)] == code:
            return rate_currency


@app.get("/{currency_code}")
def read_root(currency_code: str):
    return get_rate(currency_code)
