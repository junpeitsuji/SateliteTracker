SateliteTracker
===============

A project for Web API to predict a satelite orbit using C++ Library (OrbitTools).

Plan, Description: http://tsujimotter.info/2013/01/02/iss-api/

Web API example (JSONP script): http://tsujimotter.info/iss/orbitjsonp.cgi?callback=jsonp 

Created by Junpei Tsuji (@tsujimotter, tsuji@complex.ist.hokudai.ac.jp), 2013/1/1

=================================================================

* ISS 軌跡情報API (2013/1/4 現在)


* リクエストURL (Request URL)
JSONP: http://tsujimotter.info/iss/orbitjsonp.cgi



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
		|		| http://tsujimotter.info/iss/tle/iss20130102.tle
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
-------------------------------------------------------------------------------------------

実行例  (example of a request query. ):
http://tsujimotter.info/iss/orbitjsonp.cgi?callback=jsonp&appid=XXXXXXXXXXXXXXX&offset=120.0&intervals=0.2



* レスポンスフィールド (未実装含む) (Response JSONP fields)

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
+ orbits 			| 軌道データの配列. 下記3項目からなる. 
				| 配列のデータ数は dataNum フィールドに一致
+ orbits[i].date		| 軌道データの予測時刻 ("YYYY-MM-DD HH:mm:ss")
+ orbits[i].latitude		| 軌道予測の座標 
				| 緯度. 単位: degree [-90.0<x<90.0] 
				| 値が正のとき 北緯, 負のとき 南緯.
+ orbits[i].longitude		| 軌道予測の座標 
				| 経度. 単位: degree [0<x<360.0] 
				| 値が 180.0 より小さい時 西経, 
				| 180.0 より大きい時      東経.
---------------------------------------------------------------------------------------------


JSONP形式で返される。

レスポンステキスト例 (example of a response text. ):
---------------------------------------------------------------------------------------------
jsonp({
	"sateliteName" : "GOSAT (ISS)",
	"currentDate" : "2013-01-03 23:55:23",
	"intervalMinutes" : "0.2",
	"dataNum" : "10",
	"tleLine1" : "1 25544U 98067A   13001.52012361  .00016717  00000-0  10270-3 0  9002",
	"tleLine2" : "2 25544  51.6441 216.2888 0015668 109.9671 250.3170 15.51850049  8742",
	"algorithm" : "SGP4",
	"library" : "OrbitTools (http://www.zeptomoby.com/satellites/)",
	"orbits" : [
		{ "date" : "2013-01-03 23:55:23", 
			"latitude" : "-36.897251", 
			"longitude" : "94.819834" },
		{ "date" : "2013-01-03 23:55:35", 
			"latitude" : "-37.385592", 
			"longitude" : "95.522236" },
		{ "date" : "2013-01-03 23:55:47", 
			"latitude" : "-37.869015", 
			"longitude" : "96.234341" },
		{ "date" : "2013-01-03 23:55:59", 
			"latitude" : "-38.347375", 
			"longitude" : "96.956347" },
		{ "date" : "2013-01-03 23:56:11", 
			"latitude" : "-38.820521", 
			"longitude" : "97.688449" },
		{ "date" : "2013-01-03 23:56:23", 
			"latitude" : "-39.288299", 
			"longitude" : "98.430841" },
		{ "date" : "2013-01-03 23:56:35", 
			"latitude" : "-39.750551", 
			"longitude" : "99.183712" },
		{ "date" : "2013-01-03 23:56:47", 
			"latitude" : "-40.207116", 
			"longitude" : "99.947249" },
		{ "date" : "2013-01-03 23:56:59", 
			"latitude" : "-40.657829", 
			"longitude" : "100.721634" },
		{ "date" : "2013-01-03 23:57:11", 
			"latitude" : "-41.102521", 
			"longitude" : "101.507043" }]
})

