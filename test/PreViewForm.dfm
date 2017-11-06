object AdminLogin: TAdminLogin
  Left = 393
  Top = 218
  Width = 284
  Height = 234
  Caption = #30331#38470#31649#29702#21592#30028#38754
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object PasswordLabel: TRzLabel
    Left = 27
    Top = 78
    Width = 78
    Height = 19
    Caption = #31649#29702#21592#23494#30721#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentFont = False
  end
  object LoginIn: TRzBitBtn
    Left = 22
    Top = 160
    Caption = #30331#38470
    TabOrder = 0
    OnClick = LoginInClick
  end
  object PasswordEdit: TRzEdit
    Left = 112
    Top = 76
    Width = 129
    Height = 21
    Hint = #22312#27492#36755#20837#31649#29702#21592#23494#30721#36827#34892#39564#35777#30331#38470#65281
    PasswordChar = '*'
    TabOnEnter = True
    TabOrder = 1
  end
  object ForgetPWD: TRzBitBtn
    Left = 166
    Top = 160
    Caption = #24536#35760#23494#30721
    TabOrder = 2
    OnClick = ForgetPWDClick
  end
end
