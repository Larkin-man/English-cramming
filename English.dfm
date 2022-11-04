object Form1: TForm1
  Left = 171
  Top = 202
  Width = 610
  Height = 375
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 20
  object RLang: TRadioGroup
    Left = 0
    Top = 0
    Width = 201
    Height = 89
    Caption = #1055#1088#1077#1076#1083#1072#1075#1072#1090#1100' '#1082' '#1087#1077#1088#1077#1074#1086#1076#1091
    ItemIndex = 0
    Items.Strings = (
      #1040#1085#1075#1083#1080#1081#1089#1082#1080#1077' '#1089#1083#1086#1074#1072
      #1056#1091#1089#1089#1082#1080#1077' '#1089#1083#1086#1074#1072
      #1048' '#1090#1077' '#1080' '#1076#1088#1091#1075#1080#1077)
    TabOrder = 0
  end
  object ListBox1: TListBox
    Left = 402
    Top = 0
    Width = 200
    Height = 341
    Align = alRight
    ItemHeight = 20
    TabOrder = 1
  end
  object RusOut: TStaticText
    Left = 72
    Top = 178
    Width = 153
    Height = 41
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkSoft
    Caption = 'RusOut'
    Color = clMenu
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Book Antiqua'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 2
  end
  object GroupBox1: TGroupBox
    Left = 208
    Top = 0
    Width = 185
    Height = 105
    Caption = 'GroupBox1'
    TabOrder = 3
    object CheckBox1: TCheckBox
      Left = 8
      Top = 24
      Width = 169
      Height = 17
      Caption = #1057#1091#1097#1077#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1077
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 8
      Top = 48
      Width = 169
      Height = 17
      Caption = #1055#1088#1080#1083#1072#1075#1072#1090#1077#1083#1100#1085#1099#1077
      TabOrder = 1
    end
    object CheckBox3: TCheckBox
      Left = 8
      Top = 72
      Width = 169
      Height = 17
      Caption = #1043#1083#1072#1075#1086#1083#1099
      TabOrder = 2
    end
  end
  object EngOut: TStaticText
    Left = 72
    Top = 136
    Width = 153
    Height = 41
    Alignment = taCenter
    AutoSize = False
    BevelKind = bkSoft
    Caption = 'Word'
    Color = clBtnHighlight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Book Antiqua'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 4
  end
  object Panel2: TPanel
    Left = 168
    Top = 224
    Width = 153
    Height = 57
    Caption = #1054#1090#1074#1077#1090
    TabOrder = 5
    OnClick = Panel2Click
  end
  object Button1: TButton
    Left = 8
    Top = 224
    Width = 153
    Height = 57
    Caption = #1057#1083#1077#1076#1091#1102#1097#1080#1081
    TabOrder = 6
    OnClick = Button1Click
  end
end
