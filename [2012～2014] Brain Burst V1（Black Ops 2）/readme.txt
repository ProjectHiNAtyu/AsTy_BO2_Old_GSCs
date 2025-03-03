【情報】
　プロジェクト名　　　：Brain Burst
　バージョン　　　　　：1.2
　対応タイトル　　　　：Call of Duty Black Ops 2
　対応プラットフォーム：PC , PlayStation3 , Xbox360
　開発期間　　　　　　：2012/12/13～2014/10/21
　開発言語　　　　　　：GSC（Call of Duty専用C++）
　開発環境　　　　　　：Notepad++

【概要】
　当初の開発目的として、PC上で拡張Modの開発をして新規機能の追加をしたいという目的があったためプロジェクト始動。
　開発言語のGSCはゲーム側の専用言語なので、作成したプログラムはPC以外のプラットフォームでも動作するようになっています。
　ただしPC以外では対応機器に導入するための特殊な環境を用意しないといけない為、基本的にはPCとPS3ベースで作成しました。

【実装風景】
　上記に記載の通り、実機と特殊な環境がないと動作確認ができない為、ソースファイルと動画で分けてお渡しします。
　ソースファイル：bb_v1.cpp
　実装動画　　　：https://www.youtube.com/watch?v=-AJXua-O1PY&t=195s

【詳細】
　内部で使用している関数は全てCall of Duty標準の関数を使用しています。
　その関数を組み合わせ、新たな拡張機能を実装しています。
　例として、私が開発したもので大きかった機能はこちらになります。

　//===< Pilot Helicopter >===
　changePHeliType(code, code2, print) /* 8249行目 */
　changePHeliFov()                    /* 8257行目 */
　PHeliModellb()                      /* 8276行目 */
　PHeliModelah()                      /* 8280行目 */
　PHeliModela10()                     /* 8284行目 */
　PHeliModelstlh()                    /* 8288行目 */
　initPilotHeli()                     /* 8293行目 */
　comePilotHeli()                     /* 8310行目 */
　ridePilotHeli()                     /* 8349行目 */
　infoPHeliOn()                       /* 8380行目 */
　infoPHeliOff()                      /* 8391行目 */
　movePilotHeli()                     /* 8397行目 */
　attackPHeli()                       /* 8466行目 */
　initPHeliBomb()                     /* 8536行目 */
　initPHeliCP()                       /* 8546行目 */
　initPHeliNuke()                     /* 8569行目 */
　nukeFireEffect(PHeliNuke)           /* 8641行目 */
　weaponPHeli()                       /* 8652行目 */
　actionPHeli()                       /* 8703行目 */
　stopPilotHeli()                     /* 8724行目 */
　exitPilotHeli()                     /* 8759行目 */
　//===< Pilot Helicopter >===

　上記関数全てで、動画中の2:45から登場するヘリコプターのモーションなどを構成しております。
　また、bb_v1.cpp内部の各関数は全て自作です。
　拙い説明で申し訳ありませんが、何卒よろしくお願い致します。

　立浪豪