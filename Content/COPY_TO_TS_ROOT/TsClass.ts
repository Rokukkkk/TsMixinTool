import * as UE from "ue";

export class TsClass<T extends UE.Object> {
    private bpRef!: WeakRef<T>;

    Initialize(uObj: UE.Object): void {
        this.bpRef = new WeakRef(uObj as T);
    };

    get bpObj(): T {
        return this.bpRef.deref()!;
    }
}