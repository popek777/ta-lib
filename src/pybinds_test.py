#!/usr/bin/env python3

import mw_ta_lib as ta_lib;


def test(indicator, input):
    out = [ indicator.next_val(v) for v in input ]
    print(f'{type(indicator)} out: {out}')

def adx_test():
    c = [v for v in range(10, 40)]
    l = [v-1 for v in c]
    h = [v+1 for v in c]

    adx = ta_lib.ADX(period=5)

    adx_o=[]
    pdi_o=[]
    mdi_o=[]
    for i in range(0, len(c)):
        v = adx.next_val(close=c[i], low=l[i], high=h[i])
        if v is not None:
            adx_o.append(v.adx)
            pdi_o.append(v.pdi)
            mdi_o.append(v.mdi)
        else:
            adx_o.append(None)
            pdi_o.append(None)
            mdi_o.append(None)

    print(f'{type(adx)} adx: {adx_o}')
    print(f'{type(adx)} pdi: {pdi_o}')
    print(f'{type(adx)} mdi: {mdi_o}')

def atr_test():
    c = [v for v in range(10, 40)]
    l = [v-1 for v in c]
    h = [v+1 for v in c]

    atr = ta_lib.ATR(period=5)

    out=[]
    for i in range(0, len(c)):
        out.append(atr.next_val(close=c[i], low=l[i], high=h[i]))

    print(f'{type(atr)} : {out}')

def chaikin_money_flow_test():
    c = [v for v in range(10, 40)]
    l = [v-1 for v in c]
    h = [v+1 for v in c]
    v = [v*10 for v in c]

    cmf = ta_lib.ChaikinMoneyFlow(period=5)

    out=[]
    for i in range(0, len(c)):
        out.append(cmf.next_val(high=h[i], low=l[i], close=c[i], volume=v[i]))

    print(f'{type(cmf)} : {out}')

def correlation_test():
    x = [v for v in range(10, 40)]
    y = [v for v in x]

    cor = ta_lib.Correlation(period=5)

    out=[]
    for i in range(0, len(x)):
        out.append(cor.next_val(x=x[i], y=y[i]))

    print(f'{type(cor)} : {out}')

def covariance_test():
    x = [v for v in range(10, 40)]
    y = [v for v in x]

    cov = ta_lib.Covariance(period=5)

    out=[]
    for i in range(0, len(x)):
        out.append(cov.next_val(x=x[i], y=y[i]))

    print(f'{type(cov)} : {out}')

def macd_test():
    input = [v for v in range(10, 50)]

    macd = ta_lib.MACD(short=12, long=26, signal=9)

    macd_o=[]
    signal_o=[]
    for v in input:
        out = macd.next_val(v)
        if out is not None:
            macd_o.append(out.macd)
            signal_o.append(out.signal)
        else:
            macd_o.append(None)
            signal_o.append(None)

    print(f'{type(macd)} macd: {macd_o}')
    print(f'{type(macd)} signal: {signal_o}')


def main():

    input = [v for v in range(0, 30)]
    print(f'input: {input}')

    test(ta_lib.Diff(1), input)
    test(ta_lib.EMA(5), input)
    test(ta_lib.Median(5), input)
    test(ta_lib.PctChange(1), input)
    test(ta_lib.RSI(period=14), input)
    test(ta_lib.Shift(period=1), input)
    test(ta_lib.StdDev(period=5), input)
    test(ta_lib.SMA(period=5), input)
    test(ta_lib.Variance(period=5), input)
    test(ta_lib.Zscore(period=5), input)

    adx_test()
    atr_test()
    chaikin_money_flow_test()
    correlation_test()
    covariance_test()
    macd_test()

main()


