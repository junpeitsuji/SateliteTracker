SateliteTracker
===============

A project for Web API to predict a satelite orbit.
	RESOURCE USAGE: 
		The OrbitTools Libraries 
		URL: http://www.zeptomoby.com/satellites/
		LICENSE: "free of charge for non-commercial applications only")

Plan, Description: http://tsujimotter.info/2013/01/02/iss-api/

Web API example (JSONP script): http://tsujimotter.info/api/SateliteTracker/orbitjsonp.cgi?callback=jsonp 

Created by Junpei Tsuji (@tsujimotter, tsuji@complex.ist.hokudai.ac.jp), 2013/1/1

=================================================================

* ISS 軌跡情報API (2013/1/4 現在)


* リクエストURL (Request URL)
JSONP: http://tsujimotter.info/api/SateliteTracker/orbitjsonp.cgi



* リクエストパラメータ (未実装含む) (Request Query Parameters)

 パラメータ 	| 値 		| 説明
 (parameters)	| (value)	| (description)
-------------------------------------------------------------------------------------------
(+ appid)	| string	| アプリケーションID (未実装)
 + callback	| string	| JSONPとして出力する際のコールバック関数名を
		|		| 入力するためのパラメータ。
		|		| UTF-8でエンコードされた文字列を入力する。
 + tleid	| string	| 計算の入力に使われるTLEのIDを
		|		| 入力するためのパラメータ。
		|		| UTF-8でエンコードされた文字列を入力する。
		|		| http://tsujimotter.info/api/SateliteTracker/tle/iss20130102.tle
		|		| を入力する場合 "tleid=iss20130102" とする。
		|		| デフォルトは "tleid=iss"
(+ offset) 	| double 	| 現在時刻からどれだけの時間後方にずらした
		| 		| データを取得するか指定するパラメータ。
		|		| (単位: minites) (未実装)
(+ termination)	| double	| データ開始時刻からどれだけの時間後方までの
		| 		| データを取得するか指定するパラメータ。
		|		| (単位: minites) (未実装)
(+ intervals)	| double 	| データの取得間隔 (単位: mitutes) (未実装)
(+ method)	| string	| 軌道データの予測方式 ("SGP4", "SDP4") (未実装)

実行例  (example of a request query. ):
http://tsujimotter.info/api/SateliteTracker/orbitjsonp.cgi?callback=jsonp&appid=XXXXXXXXXXXXXXX&offset=120.0&intervals=0.2



* レスポンスフィールド (未実装含む) (Response JSONP fields)
JSONP形式で返される。

 フィールド	 (fields)	| 説明 (description)
---------------------------------------------------------------------------------------------
+ sateliteName			| 衛星名 (ISSの場合: "GOSAT (ISS)")
+ currentDate   		| APIアクセス時の日付・時刻 ("YYYY-MM-DD HH:mm:ss")
+ intervalMinutes		| 軌道データの取得間隔 (単位: minutes)
+ dataNum			| 総軌道データ数
+ tleLine1			| 予測の基となったTLE (2行軌道要素形式)　の 1行目
+ tleLine2			| 予測の基となったTLE (2行軌道要素形式)　の 2行目
+ algorithm			| 軌道データの予測方式 ("SGP4", "SDP4")
+ library			| 計算に用いた C++ のライブラリ 
				| (OrbitTools "http://www.zeptomoby.com/satellites/")
+ orbits 			| 予測軌道データの配列. 下記3項目からなる. 
				| 配列のデータ数は dataNum フィールドに一致
+ orbits[i].date		| 軌道データの予測時刻 ("YYYY-MM-DD HH:mm:ss")
+ orbits[i].latitude		| 予測軌道の座標 
				| 緯度. 単位: degree [-90.0<x<90.0] 
				| 値が正のとき 北緯, 負のとき 南緯.
+ orbits[i].longitude		| 予測軌道の座標 
				| 経度. 単位: degree [0<x<360.0] 
				| 値が 180.0 より小さい時      東経, 
				| 180.0 より大きい時 360.0-xが 西経.
+ orbits[i].altitude		| 予測軌道の高度 
				| 単位: km 


レスポンステキスト例 (example of a response text. ):
---------------------------------------------------------------------------------------------
jsonp.handler({
	"sateliteName" : "GOSAT (ISS)",
	"currentDate" : "2013-01-05 04:42:20",
	"intervalMinutes" : "0.2",
	"dataNum" : "5",
	"tleLine1" : "1 25544U 98067A   13001.52012361  .00016717  00000-0  10270-3 0  9002",
	"tleLine2" : "2 25544  51.6441 216.2888 0015668 109.9671 250.3170 15.51850049  8742",
	"algorithm" : "SGP4",
	"library" : "OrbitTools (http://www.zeptomoby.com/satellites/)",
	"orbits" : [
		{"date" : "2013-01-05 04:42:20", 
			"latitude" : "51.633563", 
			"longitude" : "255.983587", 
			"altitude" : "407.859503" },
		{"date" : "2013-01-05 04:42:32", 
			"latitude" : "51.560441", 
			"longitude" : "257.177805", 
			"altitude" : "407.775546" },
		{"date" : "2013-01-05 04:42:44", 
			"latitude" : "51.474186", 
			"longitude" : "258.367712", 
			"altitude" : "407.690333" },
		{"date" : "2013-01-05 04:42:56", 
			"latitude" : "51.374887", 
			"longitude" : "259.552628", 
			"altitude" : "407.603894" },
		{"date" : "2013-01-05 04:43:08", 
			"latitude" : "51.262644", 
			"longitude" : "260.731897", 
			"altitude" : "407.516262" }
	]
})

