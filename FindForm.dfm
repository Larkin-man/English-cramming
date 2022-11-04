object FormFind: TFormFind
  Left = 0
  Top = 0
  Caption = 'Find Form'
  ClientHeight = 282
  ClientWidth = 573
  Color = clBtnFace
  Constraints.MinHeight = 200
  Constraints.MinWidth = 419
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 18
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 573
    Height = 30
    Align = alTop
    BevelOuter = bvLowered
    Caption = 'Panel1'
    ShowCaption = False
    TabOrder = 0
    object FindEdit: TEdit
      Left = 1
      Top = 1
      Width = 496
      Height = 28
      Margins.Top = 0
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -17
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Text = 'FindEdit'
      ExplicitHeight = 29
    end
    object FindBtn: TButton
      Left = 497
      Top = 1
      Width = 75
      Height = 28
      Align = alRight
      Caption = #1048#1089#1082#1072#1090#1100
      TabOrder = 1
      OnClick = FindBtnClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 30
    Width = 573
    Height = 22
    Align = alTop
    Caption = 'Panel2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ShowCaption = False
    TabOrder = 1
    object Label1: TLabel
      Left = 1
      Top = 1
      Width = 293
      Height = 20
      Align = alClient
      Alignment = taRightJustify
      Caption = #1054#1073#1083#1072#1089#1090#1100' '#1087#1086#1080#1089#1082#1072':  '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      OnClick = Label1Click
      ExplicitLeft = 170
      ExplicitWidth = 124
      ExplicitHeight = 18
    end
    object RusBox: TRadioButton
      Left = 492
      Top = 1
      Width = 80
      Height = 20
      Align = alRight
      Caption = #1055#1077#1088#1077#1074#1086#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object TransBox: TRadioButton
      Left = 366
      Top = 1
      Width = 126
      Height = 20
      Align = alRight
      Caption = #1058#1088#1072#1085#1089#1082#1088#1080#1087#1094#1080#1103'  '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object WordBox: TRadioButton
      Left = 294
      Top = 1
      Width = 72
      Height = 20
      Align = alRight
      Caption = #1057#1083#1086#1074#1086
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      TabStop = True
    end
  end
  object Out: TStringGrid
    Left = 0
    Top = 52
    Width = 573
    Height = 230
    Align = alClient
    ColCount = 6
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
    TabOrder = 2
    OnContextPopup = OutContextPopup
    ColWidths = (
      8
      78
      22
      46
      18
      382)
  end
  object PopupMenu1: TPopupMenu
    Left = 200
    Top = 120
    object N1: TMenuItem
      Caption = #1042#1099#1074#1077#1089#1090#1080
    end
    object N2: TMenuItem
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Enabled = False
    end
  end
end
