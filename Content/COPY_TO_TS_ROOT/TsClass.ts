import * as UE from "ue";

export class TsClass<T extends UE.Object> {
    bpRef!: WeakRef<T>;
    bpClass!: T;

    Initialize(uObj: UE.Object): void { 
        this.bpClass = uObj as T;
        this.bpRef = new WeakRef(this.bpClass);
    };
}